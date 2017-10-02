#include <stdio.h>
#include <stdlib.h>
#include "modules/include/add.h"
#include "modules/include/devices.h"
#include "modules/include/oscillators.h"
#include "modules/include/whitenoise.h"

#define NUM_SECONDS 5
#define SAMPLE_RATE 48000
#define FRAMES_PER_BUFFER 64
#define CHANNELCOUNT 1 /* stereo output */

noise_t *noise;
osc_t *osc;
osc_t *osc2;
add_t *add;
add_t *add2;

static int speakerCallback(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo *timeInfo,
                           PaStreamCallbackFlags statusFlags, void *userData) {
  float *out = (float *)outputBuffer;
  unsigned long i;

  (void)timeInfo; /* Prevent unused variable warnings. */
  (void)statusFlags;
  (void)inputBuffer;

  noise->process(noise);
  osc->process(osc);
  osc2->process(osc2);
  add->process(add);
  add2->process(add2);

  for (i = 0; i < framesPerBuffer; i++) {
    out[i] = add2->output[i];
  }

  return paContinue;
}

/*
 * This routine is called by portaudio when playback is done.
 */
static void StreamFinished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  //  device_list_t *devices = create_devices();

  noise = create_noise(FRAMES_PER_BUFFER);

  osc = create_osc(0, FRAMES_PER_BUFFER, 2048);
  osc->freqValue = 440.0;
  osc->freq = NULL;
  osc->sampleRate = SAMPLE_RATE;

  osc2 = create_osc(0, FRAMES_PER_BUFFER, 2048);
  osc2->freqValue = 880.0;
  osc2->freq = NULL;
  osc2->sampleRate = SAMPLE_RATE;

  add = create_add(FRAMES_PER_BUFFER);
  add->input1 = osc->output;
  add->input2 = osc2->output;

  add2 = create_add(FRAMES_PER_BUFFER);
  add2->input1 = noise->output;
  add2->input2 = add->output;

  PaStreamParameters outputParameters;
  PaStream *stream;
  PaError err;

  err = Pa_Initialize();
  if (err != paNoError) goto error;

  outputParameters.device =
      Pa_GetDefaultOutputDevice(); /* default output device */
  if (outputParameters.device == paNoDevice) {
    fprintf(stderr, "Error: No default output device.\n");
    goto error;
  }
  outputParameters.channelCount = CHANNELCOUNT; /* stereo output */
  outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
  outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  err = Pa_OpenStream(&stream, NULL, /* no input */
                      &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER,
                      paClipOff, /* we won't output out of range samples so
                                    don't bother clipping them */
                      speakerCallback, NULL);
  if (err != paNoError) goto error;

  err = Pa_SetStreamFinishedCallback(stream, &StreamFinished);
  if (err != paNoError) goto error;

  err = Pa_StartStream(stream);
  if (err != paNoError) goto error;

  printf("Play for %d seconds.\n", NUM_SECONDS);
  Pa_Sleep(NUM_SECONDS * 1000);

  err = Pa_StopStream(stream);
  if (err != paNoError) goto error;

  err = Pa_CloseStream(stream);
  if (err != paNoError) goto error;

  Pa_Terminate();

  return err;
error:
  Pa_Terminate();
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  return err;
}
