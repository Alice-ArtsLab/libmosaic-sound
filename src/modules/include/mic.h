#ifndef mscsound_MIC_H
#define mscsound_MIC_H
typedef struct {
  float *output0;
  int framesPerBuffer;
  void (*process)(void *self, float *);
} mscsound_mic_t;

mscsound_mic_t *mscsound_create_mic(int framesPerBuffer);
void mscsound_mic_process();
#endif /* mic.h */
