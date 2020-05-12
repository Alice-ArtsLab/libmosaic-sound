#ifndef MSCSOUND_ADSR_H
#define MSCSOUND_ADSR_H

typedef struct {
  float **input0;
  float **output0;
  float *attack;
  float *decay;
  float *sustain;
  float *release;
  float *gain;
  int *play;

  int framesPerBuffer;
  int sampleRate;
  int initialSample;
  int currentSample;
  int finalSample;
  float currentAmplitude;
  int currentFrame;

  void (*process)();
} mscsound_adsr_t;

mscsound_adsr_t *mscsound_create_adsr(int sampleRate, int framesPerBuffer);

void mscsound_process_attack();
void mscsound_process_decay();
void mscsound_process_sustain();
void mscsound_process_release();
void mscsound_process_silence();

#endif /* adsr.h */
