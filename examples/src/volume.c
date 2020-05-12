#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

mscsound_playback_t *pb;
mscsound_volume_t *volume;
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
  volume->process(&volume);
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
  mscsound_gui_t *gui = mscsound_create_gui("Volume", 200, 200);

  volume = mscsound_create_volume("Volume: ", FRAMES_PER_BUFFER);

  gui->add(&gui, &(volume->widget));
  volume->input0 = pb->output0;

  speaker = mscsound_create_speaker(FRAMES_PER_BUFFER);
  speaker->input0 = volume->output0;

  void *stream = mscsound_inicialize(SAMPLE_RATE, FRAMES_PER_BUFFER);
  gui->start(&gui);

  mscsound_terminate(stream);

  return 0;
}