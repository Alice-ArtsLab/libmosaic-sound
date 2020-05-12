#ifndef MSCSOUND_RMS_H
#define MSCSOUND_RMS_H
typedef struct {
  float **input0;
  float *output0;
  int framesPerBuffer;
  void (*process)(void *self);
} mscsound_rms_t;

mscsound_rms_t *mscsound_create_rms(int framesPerBuffer);
void mscsound_rms_process();
#endif /* rms.h */
