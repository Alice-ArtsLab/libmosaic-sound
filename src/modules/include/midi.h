#ifndef MSCSOUND_MIDI_H
#define MSCSOUND_MIDI_H

typedef struct {
  void *handle;
  void (*callback)();
  void (*send_note)(void *self, int type, int channel, unsigned char vel,
                    unsigned char note);
  void (*send_control)(void *self, int channel, int control, int value);
} mscsound_midi_t;

mscsound_midi_t *mscsound_create_midi();

void mscsound_midi_send_note(void *self, int type, int channel,
                             unsigned char vel, unsigned char note);
void mscsound_midi_send_control(void *self, int channel, int control,
                                int value);
void *mscsound_midi_thread(void *data);
#endif /* midi.h */
