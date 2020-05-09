#include "include/grid.h"
#include <gtk/gtk.h>

mscsound_grid_t *mscsound_create_grid() {
  mscsound_grid_t *grid = malloc(sizeof(mscsound_grid_t));
  grid->add = mscsound_grid_add;
  grid->add_grid_in = mscsound_grid_add_in;
  grid->widget = gtk_grid_new();
  return grid;
}

void mscsound_grid_add_in(mscsound_grid_t **self, void *widget) {

  gtk_container_add(GTK_CONTAINER(*(GtkWidget **)(widget)),
                    (GtkWidget *)((*self)->widget));
}

void mscsound_grid_add(mscsound_grid_t **self, void *child, gint left, gint top,
                       gint width, gint height) {
  gtk_grid_attach(GTK_GRID((GtkWidget *)((*self)->widget)),
                  *(GtkWidget **)child, left, top, width, height);
}
