#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mosaicsound_playback_t *pb;
mosaicsound_highshelving_t *highshelving;
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
  highshelving->process(highshelving);
  speaker->process(speaker, out);

  return paContinue;
}

/*
 * This routine is called by mosaic-sound when mosaicsound_callback is done.
 */
static void mosaicsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {
  pb = mosaicsound_create_playback("examples/samples/victor_wooten_solo.wav",
                                   FRAMES_PER_BUFFER);
  pb->loop = 1;

  highshelving = mosaicsound_create_highshelving(FRAMES_PER_BUFFER);
  speaker = mosaicsound_create_speaker(FRAMES_PER_BUFFER);

  highshelving->input = pb->outputL;
  highshelving->sampleRate = SAMPLE_RATE;
  highshelving->cutOff = 1000.0;
  highshelving->gain = 1.0;
  speaker->input = highshelving->output;

  void *stream = mosaicsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mosaicsound_terminate(stream);

  return 0;
}
