#ifndef MSCSOUND_WHITENOISE_H
#define MSCSOUND_WHITENOISE_H

typedef struct {
  void (*process)(void *self);
  float **output0;
  int framesPerBuffer;
} mscsound_noise_t;

mscsound_noise_t *mscsound_create_noise(int framesPerBuffer);
void mscsound_noise_process();

#endif /* whitenoise.h */
