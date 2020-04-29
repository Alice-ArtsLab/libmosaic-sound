#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_osc_t *osc1;
mscsound_osc_t *osc2;
mscsound_audiomath_t *add;
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

  osc1->process(&osc1);
  osc2->process(&osc2);
  add->process(&add);

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
  osc1 = mscsound_create_osc(0, FRAMES_PER_BUFFER, 2048);
  osc1->sampleRate = SAMPLE_RATE;
  osc1->input0 = NULL;
  osc1->input1 = 440.0;

  /* Sawtooth 880.0 Hz*/
  osc2 = mscsound_create_osc(3, FRAMES_PER_BUFFER, 2048);
  osc2->sampleRate = SAMPLE_RATE;
  osc2->input0 = NULL;
  osc2->input1 = 880.0;

  add = mscsound_create_audiomath(FRAMES_PER_BUFFER, mscsound_add_2freq);

  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  add->input0 = osc1->output0;
  add->input1 = osc2->output0;

  speaker->input0 = add->output0;


  void *stream = mscsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mscsound_terminate(stream);

  return 0;
}
