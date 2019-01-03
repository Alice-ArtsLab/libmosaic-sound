#ifndef MOSAICSOUND_AUDIOMATH_H
#define MOSAICSOUND_MOSAICSOUND_AUDIOMATH_H

typedef struct {
  float *output0;
  float *input0;
  float *input1;
  int framesPerBuffer;
  void (*process)(void *self);
} mosaicsound_math_t;

mosaicsound_math_t *mosaicsound_create_math(int framesPerBuffer,
                                            void(*function));

void mosaicsound_add_2freq(mosaicsound_math_t *self);
void mosaicsound_sub_2freq(mosaicsound_math_t *self);
void mosaicsound_mul_2freq(mosaicsound_math_t *self);
void mosaicsound_div_2freq(mosaicsound_math_t *self);

void mosaicsound_add_freq_float(mosaicsound_math_t *self);
void mosaicsound_sub_freq_float(mosaicsound_math_t *self);
void mosaicsound_mul_freq_float(mosaicsound_math_t *self);
void mosaicsound_div_freq_float(mosaicsound_math_t *self);

#endif /* audiomath.h */
