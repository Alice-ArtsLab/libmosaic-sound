#ifndef MSCSOUND_GRID_H
#define MSCSOUND_GRID_H

typedef struct {
  void *widget;
  void (*add)(void *self, void *child, int left, int top, int width,
              int height);
} mscsound_grid_t;

mscsound_grid_t *mscsound_create_grid();
void mscsound_grid_add();

#endif /* grid.h */
