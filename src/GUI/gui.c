#include "include/gui.h"
#include <gtk/gtk.h>

void destroy(void){
   gtk_main_quit ();
}

mscsound_gui_t *mscsound_create_gui(char * title, int width, int height) {
  mscsound_gui_t * gui = malloc(sizeof(mscsound_gui_t));
  gui->start = mscsound_gui_start;

  gtk_init(NULL, NULL);

  gui->mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW((GtkWidget*)gui->mainwindow), title);
  g_signal_connect((GtkWidget*)gui->mainwindow, "destroy",G_CALLBACK(destroy),
                                                                        NULL);
  gtk_window_resize(GTK_WINDOW((GtkWidget*)gui->mainwindow), width, height);

  gui->widget = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
  gtk_container_add(GTK_CONTAINER((GtkWidget*)gui->mainwindow),
                                  (GtkWidget*)gui->widget);

  return gui;
}

void mscsound_gui_start(mscsound_gui_t ** gui) {
   gtk_widget_show_all((GtkWidget*)((*gui)->mainwindow));
   gtk_main();
}
