#ifndef MSCSOUND_PLAYBACK_H
#define MSCSOUND_PLAYBACK_H

typedef struct {
  char ** loop;  /* yes; no*/
  int channels;
  int framesPerBuffer;
  int fileSampleRate;
  int fileFrames;
  int readCount;
  char ** paused; /* yes; no*/
  float **output0; /* Mono / Left*/
  float **output1; /*  Right */
  float *file;
  char **filename;
  void (*process)(void *self);
} mscsound_playback_t;

mscsound_playback_t *mscsound_create_playback(char *filename,
                                                    int framesPerBuffer);

void mscsound_playback_process_mono();
void mscsound_playback_process_stereo();

#endif /* playback.h */
