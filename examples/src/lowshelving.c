#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_playback_t *pb;
mscsound_lowshelving_t *lowshelving;
mscsound_speaker_t *speaker;

static int mscsound_callback(const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo *timeInfo,
                             PaStreamCallbackFlags statusFlags,
                             void *userData) {
  float *in = (float *)inputBuffer;
  float *out = (float *)outputBuffer;

  (void)timeInfo; /* Prevent unused variable warnings. */
  (void)statusFlags;
  (void)userData;
  (void)in;

  pb->process(pb);
  lowshelving->process(lowshelving);
  speaker->input0 = lowshelving->output0;
  speaker->process(speaker, out);

  return paContinue;
}

/*
 * This routine is called by mscsound when mscsound_callback is done.
 */
static void mscsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  pb = mscsound_create_playback("../samples/victor_wooten_solo.wav",
                                FRAMES_PER_BUFFER);
  pb->loop = 1;

  lowshelving = mscsound_create_lowshelving(FRAMES_PER_BUFFER);
  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  lowshelving->input0 = pb->output0;
  lowshelving->sampleRate = SAMPLE_RATE;
  lowshelving->cutOff = 500.0;
  lowshelving->gain = 1.0;
  void *stream = mscsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mscsound_terminate(stream);

  return 0;
}
