#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

osc_t *osc1;
osc_t *osc2;
math_t *add;
speaker_t *speaker;

static int mosaicsound_callback(const void *inputBuffer, void *outputBuffer,
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

  osc1->process(osc1);
  osc2->process(osc2);
  add->process(add);
  speaker->process(speaker, out);

  return paContinue;
}

/*
 * This routine is called by mosaic-sound when mosaicsound_callback is done.
 */
static void mosaicsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  /* Sine 440.0 Hz */
  osc1 = create_osc(0, FRAMES_PER_BUFFER, 2048);
  osc1->sampleRate = SAMPLE_RATE;
  osc1->freqValue = 440.0;
  osc1->freq = NULL;

  /* Sawtooth 880.0 Hz*/
  osc2 = create_osc(3, FRAMES_PER_BUFFER, 2048);
  osc2->sampleRate = SAMPLE_RATE;
  osc2->freqValue = 880.0;
  osc2->freq = NULL;

  add = create_math(FRAMES_PER_BUFFER, add_2freq);
  add->input1 = osc1->output;
  add->input2 = osc2->output;

  speaker = create_speaker(FRAMES_PER_BUFFER);
  speaker->input = add->output;

  void *stream = mosaicsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mosaicsound_terminate(stream);

  return 0;
}
