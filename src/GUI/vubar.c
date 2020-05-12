#include "include/vubar.h"
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

void vubar_free(mscsound_vubar_t **vubar) {
  // free();
}

static void vubar_destroy(GtkWidget *widget, mscsound_vubar_t **vubar) {
  vubar_free(vubar);
}

static gboolean vubar_draw(GtkWidget *widget, GdkEventConfigure *event,
                           mscsound_vubar_t **vubar) {
  GdkWindow *window;
  cairo_t *cr;

  int value = 100 - *((*vubar)->input0) * 100;

  gtk_widget_get_allocated_width((GtkWidget *)((*vubar)->widget));
  gtk_widget_get_allocated_height((GtkWidget *)((*vubar)->widget));

  window = gtk_widget_get_window((GtkWidget *)((*vubar)->widget));
  cr = gdk_cairo_create(window);

  cairo_set_line_width(cr, 1);

  int i = 0;
  for (; i < 100; i++) {
    if (i < value) {
      if (i < 20) // red
        cairo_set_source_rgb(cr, 0.5, 0, 0);
      else if (i < 40) // yellow
        cairo_set_source_rgb(cr, 0.5, 0.5, 0);
      else // green
        cairo_set_source_rgb(cr, 0, 0.5, 0);
    } else {
      if (i < 20) // red
        cairo_set_source_rgb(cr, 0.9, 0, 0);
      else if (i < 40) // yellow
        cairo_set_source_rgb(cr, 0.9, 0.9, 0);
      else // green
        cairo_set_source_rgb(cr, 0, 0.9, 0);
    }

    cairo_rectangle(cr, 0, 0 + (3 * i), 20, 1.7);
    cairo_fill_preserve(cr);
    cairo_stroke(cr);
  }

  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_move_to(cr, 22, 20);
  cairo_show_text(cr, "+8");
  cairo_move_to(cr, 22, 120);
  cairo_show_text(cr, " 0");
  cairo_move_to(cr, 22, 250);
  cairo_show_text(cr, "-20");
  cairo_stroke(cr);

  /* Finish */
  cairo_destroy(cr);
  return TRUE;
}

void vubar_create(int radius, mscsound_vubar_t **vubar) {
  /* Initialize */
  (*vubar)->color = malloc(sizeof(GdkRGBA));
  gdk_rgba_parse((*vubar)->color, "green");

  /* Drawing box */
  (*vubar)->widget = gtk_drawing_area_new();
  gtk_widget_set_size_request((GtkWidget *)(*vubar)->widget, 40, 300);
  g_signal_connect(G_OBJECT((GtkWidget *)(*vubar)->widget), "draw",
                   G_CALLBACK(vubar_draw), vubar);

  g_signal_connect(G_OBJECT((GtkWidget *)(*vubar)->widget), "destroy",
                   G_CALLBACK(vubar_destroy), vubar);
}

/* --------------------------------------------------------- */
mscsound_vubar_t *mscsound_create_vubar(int framesPerBuffer) {
  mscsound_vubar_t *vubar = malloc(sizeof(mscsound_vubar_t));
  vubar->framesPerBuffer = framesPerBuffer;
  vubar->process = mscsound_vubar_process;
  vubar_create(13, &vubar);

  return vubar;
}

void mscsound_vubar_process(mscsound_vubar_t **vubar) {
  if ((*vubar)->widget == NULL)
    return;

  gtk_widget_queue_draw((GtkWidget *)(*vubar)->widget);
}
