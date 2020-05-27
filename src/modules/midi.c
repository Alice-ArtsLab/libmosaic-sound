#include "include/midi.h"
#include <alsa/asoundlib.h>
#include <pthread.h>
snd_seq_t *handle_thread;
typedef void (*mscsound_midi_t_event_callback_function)(snd_seq_event_t *event);

snd_seq_t *get_handle(mscsound_midi_t **self) {
  snd_seq_t *handle = (snd_seq_t *)((*self)->handle);
  return handle;
}

void *mscsound_midi_thread(void *data) {
  mscsound_midi_t *midi = *((mscsound_midi_t **)data);

  if (&(midi->callback) == NULL) {
    pthread_exit((void *)NULL);
  }
  snd_seq_event_t *ev;
  while (1) {
    snd_seq_event_input(handle_thread, &ev);
    (midi->callback)(ev);
  }
}

mscsound_midi_t *mscsound_create_midi(
    const char *device, int port_type,
    mscsound_midi_t_event_callback_function event_callback_function) {

  mscsound_midi_t *midi = malloc(sizeof(mscsound_midi_t));
  midi->callback = event_callback_function;

  midi->send_note = mscsound_midi_send_note;
  midi->send_control = mscsound_midi_send_control;
  midi->send_event = mscsound_midi_send_event;

  int portid;
  snd_seq_t *handle;
  if (snd_seq_open(&handle, "hw", port_type, 0) < 0) {
    return NULL;
  }
  midi->handle = handle;
  handle_thread = (snd_seq_t *)midi->handle;
  snd_seq_set_client_name(get_handle(&midi), device);

  if (port_type == SND_SEQ_OPEN_DUPLEX || port_type == SND_SEQ_OPEN_INPUT) {
    if ((portid = snd_seq_create_simple_port(
             get_handle(&midi), "input",
             SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
             SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
      return NULL;
    }
    pthread_t tid;
    pthread_create(&tid, NULL, mscsound_midi_thread, &midi);
  }

  if (port_type == SND_SEQ_OPEN_DUPLEX || port_type == SND_SEQ_OPEN_OUTPUT) {
    if ((portid = snd_seq_create_simple_port(
             get_handle(&midi), "output",
             SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
             SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
      return NULL;
    }
  }
  return midi;
}

void mscsound_midi_send_event(void *self, void *event) {
  snd_seq_event_output(get_handle(self), (snd_seq_event_t *)event);
  snd_seq_drain_output(get_handle(self));
}

void mscsound_midi_send_note(void *self, int type, int channel,
                             unsigned char vel, unsigned char note) {
  snd_seq_event_t ev;
  snd_seq_ev_clear(&ev);
  snd_seq_ev_set_source(&ev, 0);
  snd_seq_ev_set_subs(&ev);
  snd_seq_ev_set_direct(&ev);
  snd_seq_ev_set_fixed(&ev);

  ev.type = type;
  ev.data.note.channel = channel;
  ev.data.note.velocity = vel;
  ev.data.note.note = note;

  mscsound_midi_send_event(self, &ev);
}

void mscsound_midi_send_control(void *self, int channel, int control,
                                int value) {
  snd_seq_event_t ev;
  snd_seq_ev_clear(&ev);
  snd_seq_ev_set_source(&ev, 0);
  snd_seq_ev_set_subs(&ev);
  snd_seq_ev_set_direct(&ev);
  snd_seq_ev_set_fixed(&ev);

  ev.type = SND_SEQ_EVENT_CONTROLLER;
  ev.data.control.channel = channel;
  ev.data.control.param = control;
  ev.data.control.value = value;

  mscsound_midi_send_event(self, &ev);
}
