#ifndef MSCSOUND_WHITENOISE_H
#define MSCSOUND_WHITENOISE_H

typedef struct {
  void (*process)(void *self);
  float **output0;
  int framesPerBuffer;
} mscsound_whitenoise_t;

mscsound_whitenoise_t *mscsound_create_whitenoise(int framesPerBuffer);
void mscsound_whitenoise_process();

#endif /* whitenoise.h */
