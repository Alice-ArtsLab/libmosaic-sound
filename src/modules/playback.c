#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/playback.h"

playback_t *create_playback(char *filename, int framesPerBuffer) {
  playback_t *playback = malloc(sizeof(playback_t));
  playback->readCount = 0;
  playback->paused = 0;
  playback->loop = 0;
  playback->framesPerBuffer = framesPerBuffer;

  SNDFILE *sf;
  SF_INFO info;

  playback->filename = malloc(strlen(filename) + 1);
  strcpy(playback->filename, filename);

  playback->process = playback_process;
  playback->output = calloc(framesPerBuffer, sizeof(float));
  sf = sf_open(playback->filename, SFM_READ, &info);
  if (!sf) {
    printf("Not able to open input file %s.\n", playback->filename);
    puts(sf_strerror(NULL));
    return NULL;
  }

  playback->input = malloc(info.frames * sizeof(float));

  sf_read_float(sf, playback->input, info.frames);

  playback->fileFrames = info.frames;
  playback->fileSampleRate = info.samplerate;
  sf_close(sf);

  return playback;
}

void playback_process(playback_t *playback) {
  int i = 0;

  if (!playback->paused) {
    for (i = 0; i < playback->framesPerBuffer &&
                playback->readCount < playback->fileFrames;
         i++) {
      playback->output[i] = playback->input[playback->readCount];
      playback->readCount++;
      if (playback->loop && playback->readCount >= playback->fileFrames)
        playback->readCount = 0;
    }
    for (; i < playback->framesPerBuffer &&
           playback->readCount >= playback->fileFrames;
         i++) {
      playback->output[i] = 0;
    }
    return;
  } else {
    for (i = 0; i < playback->framesPerBuffer; i++) {
      playback->output[i] = 0;
    }
  }
}
