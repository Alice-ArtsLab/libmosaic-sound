#include <alsa/asoundlib.h>
#include <mosaic-sound.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_SECONDS 12
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

void midi_in(snd_seq_event_t *ev) {
  printf("Note event: %d %d %d %d      \n", ev->type, ev->data.note.channel,
         ev->data.note.velocity, ev->data.note.note);

  printf("Control event: %d %d %d %d      \n", ev->type,
         ev->data.control.channel, ev->data.control.param,
         ev->data.control.value);
}

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
  (void)out;

  return paContinue;
}

/*
 * This routine is called by mscsound when mscsound_callback is done.
 */
static void mscsound_finished(void *data) { printf("Stream Completed!\n"); }

/*******************************************************************/
int main(int argc, char *argv[]) {

  mscsound_midi_t *midi =
      mscsound_create_midi("Test", SND_SEQ_OPEN_DUPLEX, midi_in);

  void *stream = mscsound_initialize(SAMPLE_RATE, FRAMES_PER_BUFFER);

  for (int i = 0; i < 128; i++)
    printf("m: %f\tf: %f\n",
           mscsound_midi_freq_to_midi_note(mscsound_midi_midi_note_to_freq(i)),
           mscsound_midi_midi_note_to_freq(i));

  while (1) {
    midi->send_control(&midi, 0, 0, 127);
    midi->send_note(&midi, SND_SEQ_EVENT_NOTEON, 0, 127, 60);
    usleep(1000000);
    midi->send_note(&midi, SND_SEQ_EVENT_NOTEOFF, 0, 127, 60);
    usleep(1000000); // 1 segundo
    printf("bip!\n");
  }

  printf("Playing until the Enter key is pressed.\n");
  getchar();

  mscsound_terminate(stream);

  return 0;
}
