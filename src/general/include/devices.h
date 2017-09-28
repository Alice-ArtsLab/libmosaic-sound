#ifndef PORTAUDIO
#define PORTAUDIO
    #include <portaudio.h>
#endif /* PortAudio */

#ifndef MY_LIST
#define MY_LIST
    #include "../../util/include/list.h"
#endif /* LIST */

typedef struct {
    int id;
    int defaultDisplayed; /* 0: Input; 1: Output*/
	const PaDeviceInfo *deviceInfo;
}device_t;

typedef struct {
    t_list * output;
    void (*process)(void * self);
    void (*show)(void * devices);
}devices_t;

void devices_process();
void show_devices();

device_t * create_device();
devices_t * create_devices();
