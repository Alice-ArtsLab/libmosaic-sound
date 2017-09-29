#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/devices.h"

device_t *create_device(int deviceID) {
  device_t *newDevice = malloc(sizeof(device_t));
  newDevice->deviceInfo = malloc(sizeof(device_info_t));

  PaDeviceInfo *deviceInfo = (PaDeviceInfo *)Pa_GetDeviceInfo(deviceID);
  newDevice->deviceInfo->name =
      malloc(strlen(deviceInfo->name) * sizeof(deviceInfo->name));
  strcpy(newDevice->deviceInfo->name, (char *)deviceInfo->name);
  newDevice->deviceInfo->maxInputChannels = deviceInfo->maxInputChannels;
  newDevice->deviceInfo->maxOutputChannels = deviceInfo->maxOutputChannels;
  newDevice->deviceInfo->defaultSampleRate = deviceInfo->defaultSampleRate;
  newDevice->id = deviceID;

  if (deviceID == Pa_GetDefaultInputDevice()) newDevice->defaultDisplayed = 0;

  if (deviceID == Pa_GetDefaultOutputDevice()) newDevice->defaultDisplayed = 1;

  return newDevice;
}

device_list_t *create_devices() {
  device_list_t *newDevices = malloc(sizeof(device_list_t));
  newDevices->process = devices_process;
  newDevices->show = show_devices;
  return newDevices;
}

void devices_process(device_list_t *devices) {
  PaError err;

  err = Pa_Initialize();
  if (err != paNoError) goto error;

  int numDevices = Pa_GetDeviceCount();
  if (numDevices < 0) {
    printf("ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices);
    err = numDevices;
    goto error;
  }

  for (int i = 0; i < numDevices; i++) {
    device_t *newDevice = create_device(i);
    list_add_element(&(devices->output), newDevice);
  }

  Pa_Terminate();
  return;
error:
  Pa_Terminate();
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  devices->output = NULL;
}

void show_devices(device_list_t *devices) {
  int deviceID = 0;
  while (devices->output) {
    printf("--------------------------------------- device #%d ", deviceID);
    device_t *dev = (device_t *)devices->output->data;
    if (dev->defaultDisplayed == 0) {
      printf("(Input)\n");
    } else {
      printf("(Output)\n");
    }

    printf("name: %s\n", dev->deviceInfo->name);
    printf("maxInputChannels: %d\n", dev->deviceInfo->maxInputChannels);
    printf("maxOutputChannels: %d\n", dev->deviceInfo->maxOutputChannels);
    printf("defaultSampleRate: %f\n", dev->deviceInfo->defaultSampleRate);

    t_list *temp2 = devices->output->next;
    devices->output = temp2;
    deviceID++;
  }
}
