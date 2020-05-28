#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_playback_t *pb;
mscsound_biquad_t *bandpass;
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

  pb->process(&pb);
  bandpass->process(&bandpass);
  speaker->process(&speaker, &out);

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
  strcpy(*(pb->loop), "yes");
  int readCount = 0;
  pb->readCount = &readCount;

  /* Second-order bandpass*/
  bandpass = mscsound_create_biquad("bandpass", 2, FRAMES_PER_BUFFER);
  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  bandpass->input0 = pb->output0;
  bandpass->sampleRate = SAMPLE_RATE;
  float cutOff = 700.0;
  bandpass->cutOff = &cutOff;
  float slope = 300.0;
  bandpass->slope = &slope;
  speaker->input0 = bandpass->output0;

  void *stream = mscsound_initialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mscsound_terminate(stream);

  return 0;
}
