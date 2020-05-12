#ifndef MSCSOUND_GUI_H
#define MSCSOUND_GUI_H

typedef struct {
  void *widget;
  void *mainwindow;
  void (*start)(void *self);
  void (*add)(void *self, void *widget);
} mscsound_gui_t;

mscsound_gui_t *mscsound_create_gui(char *title, int width, int height);
void mscsound_gui_start();
void mscsound_gui_add();

#endif /* gui.h */
