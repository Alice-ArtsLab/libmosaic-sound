#ifndef MSCSOUND_VUBAR_H
#define MSCSOUND_VUBAR_H

typedef struct {
  float *input0;
  void *widget;
  void *color;
  void (*process)(void *self);
} mscsound_vubar_t;

mscsound_vubar_t *mscsound_create_vubar();

void mscsound_vubar_process();

#endif /* vubar.h */
