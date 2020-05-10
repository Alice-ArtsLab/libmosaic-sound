#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_osc_t *osc;
mscsound_adsr_t *adsr;
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
  adsr->process(&adsr);

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
  osc = mscsound_create_osc("sine", FRAMES_PER_BUFFER, 2048);
  osc->sampleRate = SAMPLE_RATE;
  osc->input0 = NULL;
  osc->input1 = 440.0;

  adsr = mscsound_create_adsr(SAMPLE_RATE, FRAMES_PER_BUFFER);
  adsr->attack = 1000;
  adsr->decay = 100;
  adsr->sustain = 300;
  adsr->release = 400;
  adsr->gain = 0.7;
  adsr->play = 1;

  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  adsr->input0 = osc->output0;

  speaker->input0 = adsr->output0;


  void *stream = mscsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  sleep(3);
  adsr->play = 1;
  printf("Playing until the Enter key is pressed.\n");

  getchar();
  mscsound_terminate(stream);

  return 0;
}
