#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/joystick.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "include/joystick.h"

void *mscsound_joystick_thread(void *data){
    mscsound_joystick_device_data_t * device_data 
            = (mscsound_joystick_device_data_t *)data;
    device_data->is_running = 1;
    int fd = open(device_data->device, O_RDONLY);
    if (fd < 0){
        device_data->error_callback_fn(device_data->device, "Device not found");
        device_data->is_running = 0;
        pthread_exit(NULL);
    }
    char name[128];
    if (ioctl(fd, JSIOCGNAME(sizeof(name)), name) < 0)
        strncpy(name, "Unknown", sizeof(name));
    char axes;
    ioctl(fd, JSIOCGAXES, &axes);
    char buttons;
    ioctl(fd, JSIOCGBUTTONS, &buttons);
    int driver_version;
    ioctl(fd,JSIOCGVERSION,&driver_version);

    mscsound_joystick_register_callback_fn * register_callback =
            device_data->register_callback_fn;

    if (register_callback != NULL)
        register_callback(
            device_data->device,
            name,
            axes,
            buttons,
            driver_version);

    mscsound_joystick_button_event_callback_fn * button_callback =
            device_data->button_event_callback_fn;
    mscsound_joystick_axis_event_callback_fn * axis_callback =
            device_data->axis_event_callback_fn;
    mscsound_joystick_button_event_t *btn_event = malloc(sizeof(btn_event));
    mscsound_joystick_axis_event_t *axis_event = malloc(sizeof(axis_event));
    struct js_event msg;

    while(1) {
        if(read(fd, &msg, sizeof(struct js_event)) != sizeof(struct js_event)){
            device_data->is_running = 0;
            close(fd);
            pthread_exit((void *)NULL);
        }
        switch(msg.type){
            case JS_EVENT_BUTTON:
                btn_event->button = msg.number;
                btn_event->value = msg.value;
                if (button_callback != NULL)
                    button_callback(btn_event);
                break;
            case JS_EVENT_AXIS:
                axis_event->axis = msg.number;
                axis_event->value = msg.value;
                if (axis_callback != NULL)
                    axis_callback(axis_event);
                break;
            case JS_EVENT_INIT:
                if (register_callback != NULL)
                    register_callback(
                        device_data->device,
                        name,
                        axes,
                        buttons,
                        driver_version);
                break;
        }
    }
}

mscsound_joystick_device_data_t * mscsound_joystick_inicialize(
            const char * device,
            mscsound_joystick_button_event_callback_fn * button_event_callback_fn,
            mscsound_joystick_axis_event_callback_fn * axis_event_callback_fn,
            mscsound_joystick_register_callback_fn * register_callback_fn,
            mscsound_joystick_error_callback_fn * error_callback_fn
        ){
    mscsound_joystick_device_data_t * data = 
            malloc(sizeof(mscsound_joystick_device_data_t));
    data->device = (char *) malloc(strlen(device));
    strcpy(data->device, device);
    data->button_event_callback_fn = button_event_callback_fn;
    data->axis_event_callback_fn = axis_event_callback_fn;
    data->register_callback_fn = register_callback_fn;
    data->error_callback_fn = error_callback_fn;
    data->is_running = 1;

    pthread_t tid;
    pthread_create(&tid, NULL, mscsound_joystick_thread, data);
    return data;
}

