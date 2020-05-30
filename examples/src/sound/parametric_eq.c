#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_playback_t *pb;
mscsound_parametric_eq_t *eq;
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
  eq->process(&eq);

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

  eq = mscsound_create_parametric_eq(FRAMES_PER_BUFFER);
  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  eq->input0 = pb->output0;
  eq->sampleRate = SAMPLE_RATE;
  float cutOff = 1000.0;
  eq->cutOff = &cutOff;
  float gain = 1.0;
  eq->gain = &gain;

  speaker->input0 = eq->output0;

  void *stream = mscsound_initialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mscsound_terminate(stream);

  return 0;
}
