#ifndef MSCSOUND_GRID_H
#define MSCSOUND_GRID_H

typedef struct {
  void *widget;
  void (*add)(void *self, void *child, int left, int top, int width,
              int height);
  void (*add_grid_in)(void *self, void *widget);
} mscsound_grid_t;

mscsound_grid_t *mscsound_create_grid();
void mscsound_grid_add();
void mscsound_grid_add_in();

#endif /* grid.h */
