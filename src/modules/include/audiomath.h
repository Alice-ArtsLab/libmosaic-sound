#ifndef mscsound_AUDIOMATH_H
#define mscsound_mscsound_AUDIOMATH_H

typedef struct {
  float *output0;
  float *input0;
  float *input1;
  int framesPerBuffer;
  void (*process)(void *self);
} mscsound_math_t;

mscsound_math_t *mscsound_create_math(int framesPerBuffer,
                                            void(*function));

void mscsound_add_2freq(mscsound_math_t *self);
void mscsound_sub_2freq(mscsound_math_t *self);
void mscsound_mul_2freq(mscsound_math_t *self);
void mscsound_div_2freq(mscsound_math_t *self);

void mscsound_add_freq_float(mscsound_math_t *self);
void mscsound_sub_freq_float(mscsound_math_t *self);
void mscsound_mul_freq_float(mscsound_math_t *self);
void mscsound_div_freq_float(mscsound_math_t *self);

#endif /* audiomath.h */
