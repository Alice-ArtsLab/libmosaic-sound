#ifndef MSCSOUND_LOWSHELVING_H
#define MSCSOUND_LOWSHELVING_H

typedef struct {
  float **input0;
  float **output0;
  float gain;
  int framesPerBuffer;
  float sampleRate;
  float cutOff;
  float xn1; /* x(n-1) */
  float xn2; /* x(n-2) */
  float yn1; /* y(n-1) */
  float yn2; /* y(n-2) */
  void (*process)(void *self);
} mscsound_lowshelving_t;

mscsound_lowshelving_t *mscsound_create_lowshelving(int framesPerBuffer);
void mscsound_lowshelving_process();

#endif /* lowshelving.h */
