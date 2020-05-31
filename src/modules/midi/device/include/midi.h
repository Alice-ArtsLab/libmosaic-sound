#ifndef MSCSOUND_MIDI_H
#define MSCSOUND_MIDI_H

typedef struct {
  void *handle;
  void (*callback)(); /* MIDI in */
  void (*send_note)(void *self, int type, int channel, unsigned char vel,
                    unsigned char note);
  void (*send_control)(void *self, int channel, int control, int value);
  void (*send_event)(void *self, void *ev);
  float (*midi_note_to_freq)(float midiNote);
  float (*freq_to_midi_note)(float frequency);
} mscsound_midi_t;

mscsound_midi_t *mscsound_create_midi();

void mscsound_midi_send_note(void *self, int type, int channel,
                             unsigned char vel, unsigned char note);
void mscsound_midi_send_control(void *self, int channel, int control,
                                int value);
void mscsound_midi_send_event(void *self, void *ev);
float mscsound_midi_midi_note_to_freq(float midiNote);
float mscsound_midi_freq_to_midi_note(float frequency);
void *mscsound_midi_thread(void *data);
void mscsound_midi_initialize();
#endif /* midi.h */
