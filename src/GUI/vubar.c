#include "include/vubar.h"
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

void vubar_free(mscsound_vubar_t **vubar) {
  // free();
}

static void vubar_destroy(GtkWidget *widget, gpointer data) {
  mscsound_vubar_t **vubar = (mscsound_vubar_t **)data;
  vubar_free(vubar);
}

static gboolean vubar_draw(GtkWidget *widget, GdkEventConfigure *event,
                           gpointer data) {

  mscsound_vubar_t **vubar = (mscsound_vubar_t **)data;

  int value = 100 - *((*vubar)->input0) * 100;

  GdkWindow *window = gtk_widget_get_window(widget);

  cairo_region_t *cairoRegion = cairo_region_create();

  GdkDrawingContext *drawingContext;
  drawingContext = gdk_window_begin_draw_frame(window, cairoRegion);

  {
    // Start drawing"
    cairo_t *cr = gdk_drawing_context_get_cairo_context(drawingContext);
    { // draw
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
    }

    // Finished drawing
    gdk_window_end_draw_frame(window, drawingContext);
  }

  // cleanup
  cairo_region_destroy(cairoRegion);
  return FALSE;
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
mscsound_vubar_t *mscsound_create_vubar() {
  mscsound_vubar_t *vubar = malloc(sizeof(mscsound_vubar_t));
  vubar->process = mscsound_vubar_process;
  vubar_create(13, &vubar);

  return vubar;
}

void mscsound_vubar_process(mscsound_vubar_t **vubar) {
  if ((*vubar)->widget == NULL)
    return;

  gtk_widget_queue_draw((GtkWidget *)(*vubar)->widget);
}
