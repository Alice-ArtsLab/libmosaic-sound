#include "include/devices.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


device_t * create_device(int device_id) {

    device_t * new_device = malloc(sizeof(device_t) );
    new_device->deviceInfo = malloc(sizeof(device_info_t));

    PaDeviceInfo *deviceInfo = (PaDeviceInfo *) Pa_GetDeviceInfo(device_id);
    new_device->deviceInfo->name = malloc(strlen(deviceInfo->name)*sizeof(deviceInfo->name));
    strcpy(new_device->deviceInfo->name , (char *)deviceInfo->name);
    new_device->deviceInfo->maxInputChannels = deviceInfo->maxInputChannels;
    new_device->deviceInfo->maxOutputChannels = deviceInfo->maxOutputChannels;
    new_device->deviceInfo->defaultSampleRate = deviceInfo->defaultSampleRate;
    new_device->id = device_id;

    if(device_id == Pa_GetDefaultInputDevice())
        new_device->defaultDisplayed = 0;

    if(device_id == Pa_GetDefaultOutputDevice())
        new_device->defaultDisplayed = 1;

    return new_device;
}

device_list_t * create_devices() {
    device_list_t *new_devices = malloc(sizeof(device_list_t));
    new_devices->process = devices_process;
    new_devices->show = show_devices;
    return new_devices;
}


void devices_process(device_list_t * devices){
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
         device_t * new_device =  create_device(i);
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

void show_devices(device_list_t * devices){
    int id_device = 0;
    while(devices->output){
        printf("--------------------------------------- device #%d ", id_device);
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
