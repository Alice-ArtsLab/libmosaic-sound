#include <alsa/asoundlib.h>
#include <portaudio.h>
#include <stdio.h>
#include <unistd.h>
#include <mosaic-sound.h>

static void mscsound_finished(void *data) { printf("Stream Completed!\n"); }

static int mscsound_callback(
            const void *inputBuffer,
            void *outputBuffer,
            unsigned long framesPerBuffer,
            const PaStreamCallbackTimeInfo *timeInfo,
            PaStreamCallbackFlags statusFlags,
            void *userData) {
  (void)inputBuffer;
  (void)outputBuffer;
  (void)timeInfo; /* Prevent unused variable warnings. */
  (void)statusFlags;
  (void)userData;
  return paContinue;
}



void button_callback(mscsound_joystick_button_event_t *event) {
    printf("Button: %d, Value: %d\n", event->button, event->value);
}

void axis_callback(mscsound_joystick_axis_event_t *event) {
    printf("Axis: %d, Value: %d\n", event->axis, event->value);
}

void error_callback(
                char * device,
                char * error_message){
    printf("device: %s \n", device);
    printf("error message: %s \n", error_message);
}

void register_callback(
                char * device,
                char * name,
                char axes,
                char buttons,
                int driver_version){
    printf("device: %s \n", device);
    printf("name: %s \n", name);
    printf("number_of_axes: %d\n", axes);
    printf("number_of_buttons: %d\n", buttons);
    printf("driver_version: %d\n", driver_version);
}


int main(int argc, char *argv[]) {
    mscsound_joystick_device_data_t * data = mscsound_joystick_inicialize(
                "/dev/input/js1",
                &button_callback,
                &axis_callback,
                &register_callback,
                &error_callback);
    while(data->is_running) usleep(10000);
    return 0;
}

