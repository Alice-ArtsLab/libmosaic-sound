#ifndef MSCSOUND_PARAMETRIC_EQUALIZER_H
#define MSCSOUND_PARAMETRIC_EQUALIZER_H

typedef struct {
  float **input0;
  float **output0;
  int framesPerBuffer;
  float sampleRate;
  float *gain;
  float *cutOff;
  float xn1; /* x(n-1) */
  float xn2; /* x(n-2) */
  float yn1; /* y(n-1) */
  float yn2; /* y(n-2) */
  void (*process)(void *self);
} mscsound_parametric_eq_t;

mscsound_parametric_eq_t *mscsound_create_parametric_eq(int framesPerBuffer);
void mscsound_parametric_eq_process();

#endif /* parametric_equalizer.h */
