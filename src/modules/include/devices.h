#ifndef MOSAICSOUND_DEVICES_H
#define MOSAICSOUND_MOSAICSOUND_DEVICES_H

    #ifndef MOSAICSOUND_PORTAUDIO
    #define MOSAICSOUND_PORTAUDIO
        #include <portaudio.h>
    #endif /* PortAudio */

    typedef struct {
            char *name;
            int maxInputChannels;
            int maxOutputChannels;
            float defaultSampleRate;
    }mosaicsound_device_info_t;

    typedef struct {
            int id;
            int defaultDisplayed; /* 0: Input; 1: Output*/
            mosaicsound_device_info_t *deviceInfo;
    }mosaicsound_device_t;

    typedef struct {
            void *output;
            void (*process)(void *self);
            void (*show)(void *devices);
    }mosaicsound_device_list_t;


    void mosaicsound_devices_process();
    void mosaicsound_show_devices();

    mosaicsound_device_t* mosaicsound_create_device(int deviceID);
    mosaicsound_device_list_t* mosaicsound_create_devices();

#endif /* devices.h */
