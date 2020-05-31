#include "include/waveform.h"
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

void waveform_free(mscsound_waveform_t **waveform) {
  // free();
}

static void waveform_destroy(GtkWidget *widget, gpointer data) {
  mscsound_waveform_t **waveform = (mscsound_waveform_t **)data;
  waveform_free(waveform);
}

static gboolean waveform_draw(GtkWidget *widget, GdkEventConfigure *event,
                              gpointer data) {

  mscsound_waveform_t **waveform = (mscsound_waveform_t **)data;

  GdkWindow *window = gtk_widget_get_window(widget);

  cairo_region_t *cairoRegion = cairo_region_create();

  GdkDrawingContext *drawingContext;
  drawingContext = gdk_window_begin_draw_frame(window, cairoRegion);

  {
    // Start drawing"
    cairo_t *cr = gdk_drawing_context_get_cairo_context(drawingContext);
    { // draw
      cairo_translate(cr, 100, 100);
      cairo_set_source_rgb(cr, 0, 0, 1);
      cairo_set_line_width(cr, 1);

      cairo_move_to(cr, 0, (*((*waveform)->input0))[0] * 100);
      int i = 1;
      for (i = 1; i < (*waveform)->framesPerBuffer; i++)
        cairo_line_to(cr, i * 2, (*((*waveform)->input0))[i] * 100);
      cairo_stroke(cr);
    }

    // Finished drawing
    gdk_window_end_draw_frame(window, drawingContext);
  }

  // cleanup
  cairo_region_destroy(cairoRegion);
  return FALSE;
}

void waveform_create(mscsound_waveform_t **waveform, int width, int height) {
  /* Initialize */

  /* Drawing box */
  (*waveform)->widget = gtk_drawing_area_new();
  gtk_widget_set_size_request((GtkWidget *)(*waveform)->widget, width, height);
  g_signal_connect(G_OBJECT((GtkWidget *)(*waveform)->widget), "draw",
                   G_CALLBACK(waveform_draw), waveform);

  g_signal_connect(G_OBJECT((GtkWidget *)(*waveform)->widget), "destroy",
                   G_CALLBACK(waveform_destroy), waveform);
}

/* --------------------------------------------------------- */
mscsound_waveform_t *mscsound_create_waveform(int width, int height,
                                              int framesPerBuffer) {
  mscsound_waveform_t *waveform = malloc(sizeof(mscsound_waveform_t));
  waveform->process = mscsound_waveform_process;
  waveform->framesPerBuffer = framesPerBuffer;
  waveform_create(&waveform, width, height);

  return waveform;
}

void mscsound_waveform_process(mscsound_waveform_t **waveform) {
  if ((*waveform)->widget == NULL)
    return;

  gtk_widget_queue_draw((GtkWidget *)(*waveform)->widget);
}
