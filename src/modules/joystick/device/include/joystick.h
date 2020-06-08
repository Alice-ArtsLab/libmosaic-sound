#ifndef MSCSOUND_JOYSTICK_H
#define MSCSOUND_JOYSTICK_H

typedef struct {
    int button;
    int value;
} mscsound_joystick_button_event_t;

typedef struct {
    int axis;
    int value;
} mscsound_joystick_axis_event_t;

typedef void (
        mscsound_joystick_button_event_callback_fn)(
        mscsound_joystick_button_event_t *event
);

typedef void (
        mscsound_joystick_axis_event_callback_fn)(
        mscsound_joystick_axis_event_t *event
);

typedef void (mscsound_joystick_register_callback_fn)(
    char * device,
    char * name,
    char number_of_axes,
    char number_of_buttons,
    int driver_version
);

typedef void (mscsound_joystick_error_callback_fn)(
    char * device,
    char * error_message
);

typedef struct {
    mscsound_joystick_button_event_callback_fn * button_event_callback_fn;
    mscsound_joystick_axis_event_callback_fn * axis_event_callback_fn;
    mscsound_joystick_register_callback_fn * register_callback_fn;
    mscsound_joystick_error_callback_fn * error_callback_fn;
    char * device;
    int is_running;
} mscsound_joystick_device_data_t;

void *mscsound_joystick_thread(void *data);

mscsound_joystick_device_data_t * mscsound_joystick_inicialize(
    const char * device,
    mscsound_joystick_button_event_callback_fn * button_event_callback_fn,
    mscsound_joystick_axis_event_callback_fn * axis_event_callback_fn,
    mscsound_joystick_register_callback_fn * register_callback_fn,
    mscsound_joystick_error_callback_fn * error_callback_fn
);
#endif /* joystick.h */
