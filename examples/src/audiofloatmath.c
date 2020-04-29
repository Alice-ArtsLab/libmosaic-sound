#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_osc_t *osc;
mscsound_audiofloatmath_t *mul;
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

  osc->process(&osc);
  mul->process(&mul);

  speaker->process(&speaker, &out);

  return paContinue;
}

/*
 * This routine is called by mscsound when mscsound_callback is done.
 */
static void mscsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  /* Sine 440.0 Hz */
  osc = mscsound_create_osc(0, FRAMES_PER_BUFFER, 2048);
  osc->sampleRate = SAMPLE_RATE;
  osc->input0 = NULL;
  osc->input1 = 440.0;

  mul = mscsound_create_audiofloatmath(FRAMES_PER_BUFFER, mscsound_mul_freq_float);

  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  mul->input0 = osc->output0;
  mul->input1 = 0.01;

  speaker->input0 = mul->output0;


  void *stream = mscsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mscsound_terminate(stream);

  return 0;
}
