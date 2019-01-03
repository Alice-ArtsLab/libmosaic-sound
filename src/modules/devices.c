#include "../util/include/list.h"
#include "include/devices.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mosaicsound_device_t *mosaicsound_create_device(int deviceID) {
  mosaicsound_device_t *newDevice = malloc(sizeof(mosaicsound_device_t));
  newDevice->deviceInfo = malloc(sizeof(mosaicsound_device_info_t));

  PaDeviceInfo *deviceInfo = (PaDeviceInfo *)Pa_GetDeviceInfo(deviceID);
  newDevice->deviceInfo->name =
      malloc(strlen(deviceInfo->name) * sizeof(deviceInfo->name));
  strcpy(newDevice->deviceInfo->name, (char *)deviceInfo->name);
  newDevice->deviceInfo->maxInputChannels = deviceInfo->maxInputChannels;
  newDevice->deviceInfo->maxOutputChannels = deviceInfo->maxOutputChannels;
  newDevice->deviceInfo->defaultSampleRate = deviceInfo->defaultSampleRate;
  newDevice->id = deviceID;

  if (deviceID == Pa_GetDefaultInputDevice())
    newDevice->defaultDisplayed = 0;

  if (deviceID == Pa_GetDefaultOutputDevice())
    newDevice->defaultDisplayed = 1;

  return newDevice;
}

mosaicsound_device_list_t *mosaicsound_create_devices() {
  mosaicsound_device_list_t *newDevices =
      malloc(sizeof(mosaicsound_device_list_t));
  newDevices->process = mosaicsound_devices_process;
  newDevices->show = mosaicsound_show_devices;
  return newDevices;
}

void mosaicsound_devices_process(mosaicsound_device_list_t *devices) {
  PaError err;

  err = Pa_Initialize();
  if (err != paNoError)
    goto error;

  int numDevices = Pa_GetDeviceCount();
  if (numDevices < 0) {
    printf("ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices);
    err = numDevices;
    goto error;
  }

  for (int i = 0; i < numDevices; i++) {
    mosaicsound_device_t *newDevice = mosaicsound_create_device(i);
    mosaicsound_list_add_element((mosaicsound_list_t **)&(devices->output0),
                                 newDevice);
  }

  Pa_Terminate();
  return;
error:
  Pa_Terminate();
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  devices->output0 = NULL;
}

void mosaicsound_show_devices(mosaicsound_device_list_t *devices) {
  int deviceID = 0;
  while (devices->output0) {
    printf("--------------------------------------- device #%d ", deviceID);
    mosaicsound_device_t *dev =
        (mosaicsound_device_t *)((mosaicsound_list_t *)devices->output0)->data;
    if (dev->defaultDisplayed == 0)
      printf("(Input)\n");
    else
      printf("(Output)\n");

    printf("name: %s\n", dev->deviceInfo->name);
    printf("maxInputChannels: %d\n", dev->deviceInfo->maxInputChannels);
    printf("maxOutputChannels: %d\n", dev->deviceInfo->maxOutputChannels);
    printf("defaultSampleRate: %f\n", dev->deviceInfo->defaultSampleRate);

    mosaicsound_list_t *temp2 = ((mosaicsound_list_t *)devices->output0)->next;
    devices->output0 = temp2;
    deviceID++;
  }
}
