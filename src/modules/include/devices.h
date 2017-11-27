#ifndef DEVICES_H
#define DEVICES_H

    #ifndef PORTAUDIO
    #define PORTAUDIO
        #include <portaudio.h>
    #endif /* PortAudio */

    typedef struct {
            char *name;
            int maxInputChannels;
            int maxOutputChannels;
            float defaultSampleRate;
    }device_info_t;

    typedef struct {
            int id;
            int defaultDisplayed; /* 0: Input; 1: Output*/
            device_info_t *deviceInfo;
    }device_t;

    typedef struct {
            void *output;
            void (*process)(void *self);
            void (*show)(void *devices);
    }device_list_t;


    void devices_process();
    void show_devices();

    device_t* create_device(int deviceID);
    device_list_t* create_devices();

#endif /* devices.h */
