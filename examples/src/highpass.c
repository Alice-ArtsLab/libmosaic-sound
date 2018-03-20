#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mosaicsound_playback_t *pb;
mosaicsound_biquad_t *highpass;
mosaicsound_speaker_t *speaker;

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

  pb->process(pb);
  highpass->process(highpass);
  speaker->process(speaker, out);

  return paContinue;
}

/*
 * This routine is called by mosaic-sound when mosaicsound_callback is done.
 */
static void mosaicsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  pb = mosaicsound_create_playback("../samples/victor_wooten_solo.wav",
                                   FRAMES_PER_BUFFER);
  pb->loop = 1;

  /* Second-order highpass*/
  highpass = mosaicsound_create_biquad(2, 2, FRAMES_PER_BUFFER);
  speaker = mosaicsound_create_speaker(FRAMES_PER_BUFFER);

  highpass->input0 = pb->output0;
  highpass->sampleRate = SAMPLE_RATE;
  highpass->cutOff = 900.0;
  highpass->slope = 0.2;
  speaker->input0 = highpass->output0;

  void *stream = mosaicsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mosaicsound_terminate(stream);

  return 0;
}
