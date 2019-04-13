#ifndef mscsound_BIQUAD_H
#define mscsound_mscsound_BIQUAD_H

typedef struct {
  int type;  /*0: Allpass; 1: Lowpass; 2: Highpass; 3: Bandpass; 4: Bandreject*/
  int order; /*1: First-order; 2: Second-order*/
  float *input0;
  float *output0;
  int framesPerBuffer;
  float sampleRate;
  float slope;
  float cutOff;
  float xn1; /* x(n-1) */
  float xn2; /* x(n-2) */
  float yn1; /* y(n-1) */
  float yn2; /* y(n-2) */
  void (*process)(void *self);
} mscsound_biquad_t;

mscsound_biquad_t *mscsound_create_biquad(int type, int order,
                                                int framesPerBuffer);

void mscsound_allpass_process();
void mscsound_lowpass_process();
void mscsound_highpass_process();
void mscsound_bandpass_process();
void mscsound_bandreject_process();

#endif /* biquad.h */
