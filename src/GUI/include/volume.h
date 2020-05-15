#ifndef MSCSOUND_VOLUME_H
#define MSCSOUND_VOLUME_H

typedef struct {
  float *output0;
  void *widget;
} mscsound_volume_t;

mscsound_volume_t *mscsound_create_volume(char *labelValue);
#endif /* volume.h */
