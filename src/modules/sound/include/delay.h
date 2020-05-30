#ifndef MSCSOUND_DELAY_H
#define MSCSOUND_DELAY_H
typedef struct {
  float **input0;
  float *buffer;
  int bufferSize;
  float *time;
  int startWrite;
  int startRead;
  float **output0;
  int framesPerBuffer;
  int sampleRate;
  void (*process)(void *self);
} mscsound_delay_t;

mscsound_delay_t *mscsound_create_delay(float time, int framesPerBuffer,
                                        int sampleRate);
void mscsound_delay_process();
#endif /* delay.h */
