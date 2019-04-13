#ifndef MSCSOUND_OSCILLATORS_H
#define MSCSOUND_OSCILLATORS_H

typedef struct {
  float *table;
  int tableSize;
  int index;
  int type;      /*0: Sine; 1: Square; 2: Triangle; 3: Sawtooth.*/
  float *input0; /* freq*/
  float input1;  /* freqValue */
  float *output0;
  int framesPerBuffer;
  float sampleRate;
  void (*process)(void *self);
} mscsound_osc_t;

mscsound_osc_t *mscsound_create_osc(int type, int framesPerBuffer,
                                          float tableSize);
void mscsound_osc_process();

float *mscsound_create_sine_table(int size);
float *mscsound_create_square_table(int size);
float *mscsound_create_triangle_table(int size);
float *mscsound_create_sawtooth_table(int size);
float mscsound_get_interpolated_freq(mscsound_osc_t *osc);

#endif /* oscillators.h */
