#include "include/volume.h"
#include <gtk/gtk.h>
#include <stdio.h>
mscsound_volume_t *volumeCopy;
static gboolean mscsound_volume_event(GtkScaleButton *widget,
                                      GdkEventConfigure *event,
                                      mscsound_volume_t **volume) {
  volumeCopy->value = gtk_scale_button_get_value(widget);
}
mscsound_volume_t *mscsound_create_volume(char *labelValue) {
  mscsound_volume_t *volume = malloc(sizeof(mscsound_volume_t));
  volume->output0 = calloc(1, sizeof(float *));
  volume->process = mscsound_volume_process;
  volumeCopy = volume;

  volume->value = 0.0;

  GtkWidget *volumeButton;
  GtkWidget *label;

  volume->widget = gtk_grid_new();

  label = gtk_label_new(labelValue);
  gtk_grid_attach(GTK_GRID((GtkWidget *)volume->widget), label, 1, 1, 1, 1);

  volumeButton = gtk_volume_button_new();
  gtk_grid_attach(GTK_GRID((GtkWidget *)volume->widget), volumeButton, 2, 1, 1,
                  1);
  g_signal_connect(volumeButton, "value-changed",
                   G_CALLBACK(mscsound_volume_event), &volume);

  return volume;
}

void mscsound_volume_process(mscsound_volume_t **self) {
  *((*self)->output0) = *((*self)->input0);
  for (int i = 0; i < 256; i++) {
    (*((*self)->output0))[i] *= (*self)->value;
  }
}
