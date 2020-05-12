#ifndef MSCSOUND_AUDIOFLOATMATH_H
#define MSCSOUND_AUDIOFLOATMATH_H

typedef struct {
  float **output0;
  float **input0;
  float *input1;
  int framesPerBuffer;
  void (*process)(void *self);
} mscsound_audiofloatmath_t;

mscsound_audiofloatmath_t *mscsound_create_audiofloatmath(int framesPerBuffer,
                                                          void(*function));

void mscsound_add_freq_float();
void mscsound_sub_freq_float();
void mscsound_mul_freq_float();
void mscsound_div_freq_float();

#endif /* audiofloatmath.h */
