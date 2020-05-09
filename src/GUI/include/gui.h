#ifndef MSCSOUND_GUI_H
#define MSCSOUND_GUI_H

typedef struct {
  void *widget;
  void *mainwindow;
  void (*start)(void *self);
} mscsound_gui_t;

mscsound_gui_t *mscsound_create_gui(char * title, int width, int height);
void mscsound_gui_start();

#endif /* gui.h */
