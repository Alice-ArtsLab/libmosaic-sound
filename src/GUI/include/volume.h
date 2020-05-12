#ifndef MSCSOUND_VOLUME_H
#define MSCSOUND_VOLUME_H

typedef struct {
  float **output0;
  float **input0;
  void (*process)(void *self);
  float value;
  void *widget;
} mscsound_volume_t;

mscsound_volume_t *mscsound_create_volume(char *labelValue);
void mscsound_volume_process();
#endif /* volume.h */
