#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

playback_t *pb;
parametric_eq_t *eq;

static int mosaicsound_callback(const void *inputBuffer, void *outputBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *timeInfo,
                                PaStreamCallbackFlags statusFlags,
                                void *userData) {
  float *in = (float *)inputBuffer;
  float *out = (float *)outputBuffer;
  unsigned long i;

  (void)timeInfo; /* Prevent unused variable warnings. */
  (void)statusFlags;
  (void)userData;
  (void)in;

  pb->process(pb);
  eq->process(eq);

  for (i = 0; i < framesPerBuffer; i++) {
    out[i] = eq->output[i];
  }

  return paContinue;
}

/*
 * This routine is called by mosaic-sound when mosaicsound_callback is done.
 */
static void mosaicsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  pb = create_playback("examples/samples/victor_wooten_solo.wav",
                       FRAMES_PER_BUFFER);
  pb->loop = 1;

  eq = create_parametric_eq(FRAMES_PER_BUFFER);

  eq->input = pb->outputL;
  eq->sampleRate = SAMPLE_RATE;
  eq->cutOff = 1000.0;
  eq->slope = 0.2;
  eq->gain = 1.0;

  void *stream = mosaicsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mosaicsound_terminate(stream);

  return 0;
}
