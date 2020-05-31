#ifndef MSCSOUND_WAVEFORM_H
#define MSCSOUND_WAVEFORM_H

typedef struct {
  float **input0;
  int framesPerBuffer;
  void *widget;
  void (*process)(void *self);
} mscsound_waveform_t;

mscsound_waveform_t *mscsound_create_waveform(int width, int height,
                                              int framesPerBuffer);

void mscsound_waveform_process();

#endif /* waveform.h */
