#ifndef MSCSOUND_AUDIOMATH_H
#define MSCSOUND_AUDIOMATH_H

typedef struct {
  float **output0;
  float **input0;
  float **input1;
  int framesPerBuffer;
  void (*process)(void *self);
} mscsound_audiomath_t;

mscsound_audiomath_t *mscsound_create_audiomath(int framesPerBuffer,
                                            void(*function));

void mscsound_add_2freq();
void mscsound_sub_2freq();
void mscsound_mul_2freq();
void mscsound_div_2freq();

#endif /* audiomath.h */
