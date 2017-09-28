#include "include/devices.h"
#include <stdlib.h>
#include <stdio.h>


device_t * create_device() {
    device_t *new_device = malloc(sizeof(device_t));
    new_device->deviceInfo = malloc(sizeof(PaDeviceInfo));

    return new_device;
}

devices_t * create_devices() {
    devices_t *new_devices = malloc(sizeof(devices_t));
    new_devices->process = devices_process;
    new_devices->show = show_devices;
    return new_devices;
}


void devices_process(devices_t * devices){
	PaError err;

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

     int numDevices = Pa_GetDeviceCount();
     if( numDevices < 0 ){
         printf( "ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices );
         err = numDevices;
         goto error;
     }

     for(int i=0; i<numDevices; i++){
         device_t * new_device =  create_device();
         new_device->deviceInfo = Pa_GetDeviceInfo( i );
          new_device->id = i;

     /* Mark global and API specific default devices */

         if( i == Pa_GetDefaultInputDevice() )
             new_device->defaultDisplayed = 0;


         if( i == Pa_GetDefaultOutputDevice() )
             new_device->defaultDisplayed = 1;


         list_add_element(&(devices->output), new_device);
    }

    Pa_Terminate();
    return;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    devices->output = NULL;

}

void show_devices(devices_t * devices){
    int id_device = 0;
    while(devices->output){
        printf( "--------------------------------------- device #%d ", id_device );
        device_t * dev = (device_t *)devices->output->data;
        if (dev->defaultDisplayed == 0) {
            printf("(Input)\n");
        } else {
            printf( "(Output)\n");
        }

        printf ("name: %s\n", dev->deviceInfo->name);
        printf ("maxInputChannels: %d\n", dev->deviceInfo->maxInputChannels);
        printf ("maxOutputChannels: %d\n", dev->deviceInfo->maxOutputChannels);
        printf ("defaultSampleRate: %f\n", dev->deviceInfo->defaultSampleRate);

        t_list * temp2 = devices->output->next;
        devices->output = temp2;
        id_device++;
    }

}
