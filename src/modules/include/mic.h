#ifndef MOSAICSOUND_MIC_H
#define MOSAICSOUND_MIC_H
typedef struct {
  float *output0;
  int framesPerBuffer;
  void (*process)(void *self, float *);
} mosaicsound_mic_t;

mosaicsound_mic_t *mosaicsound_create_mic(int framesPerBuffer);
void mosaicsound_mic_process();
#endif /* mic.h */
