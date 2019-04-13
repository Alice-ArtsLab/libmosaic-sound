#ifndef mscsound_PLAYBACK_H
#define mscsound_PLAYBACK_H

typedef struct {
  int loop;
  int channels;
  int framesPerBuffer;
  int fileSampleRate;
  int fileFrames;
  int readCount;
  int paused;     /* 0: paused ; 1: playing*/
  float *output0; /* Left*/
  float *output1; /*  Right */
  float *file;
  char *filename;
  void (*process)(void *self);
} mscsound_playback_t;

mscsound_playback_t *mscsound_create_playback(char *filename,
                                                    int framesPerBuffer);

void mscsound_playback_process_mono();
void mscsound_playback_process_stereo();

#endif /* playback.h */
