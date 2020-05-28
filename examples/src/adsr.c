#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
  srand((unsigned int)time(NULL));
  /* Sine */
  osc = mscsound_create_osc("sine", FRAMES_PER_BUFFER, 2048);
  osc->sampleRate = SAMPLE_RATE;
  osc->input0 = NULL;
  float freqValue = (float)(rand() % 2000);
  osc->input1 = &freqValue;

  adsr = mscsound_create_adsr(SAMPLE_RATE, FRAMES_PER_BUFFER);

  float attack = 300;
  adsr->attack = &attack;
  float decay = 30;
  adsr->decay = &decay;
  float sustain = 50;
  adsr->sustain = &sustain;
  float release = 100;
  adsr->release = &release;
  float gain = 0.7;
  adsr->gain = &gain;
  int play = 1;
  adsr->play = &play;

  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);

  adsr->input0 = osc->output0;

  speaker->input0 = adsr->output0;

  void *stream = mscsound_initialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  while (1) {
    printf("Frequency value: %.2f Hz\n", *(osc->input1));
    usleep(600000);
    *(osc->input1) = (float)(rand() % 2000);
    *(adsr->play) = 1;
  }
  printf("Playing until the Enter key is pressed.\n");

  getchar();
  mscsound_terminate(stream);

  return 0;
}
