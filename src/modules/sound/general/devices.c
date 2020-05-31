#include "include/devices.h"
#include "../../util/list/include/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mscsound_device_t *mscsound_create_device(int deviceID) {
  mscsound_device_t *newDevice = malloc(sizeof(mscsound_device_t));
  newDevice->deviceInfo = malloc(sizeof(mscsound_device_info_t));

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

mscsound_device_list_t *mscsound_create_devices() {
  mscsound_device_list_t *newDevices = malloc(sizeof(mscsound_device_list_t));
  newDevices->output1 = calloc(1, sizeof(char *));
  newDevices->process = mscsound_devices_process;
  newDevices->show = mscsound_show_devices;
  newDevices->output0 = calloc(1, sizeof(void *));
  newDevices->output0[0] = NULL;

  newDevices->lenOutput1 = 2000;
  *(newDevices->output1) = calloc(newDevices->lenOutput1, sizeof(char));
  strcpy(*(newDevices->output1), "");
  return newDevices;
}

void mscsound_devices_process(mscsound_device_list_t **devices) {
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

  if (*((*devices)->output0) != NULL) {
    mscsound_list_free(*((*devices)->output0));
    *((*devices)->output0) = NULL;
  }

  for (int i = 0; i < numDevices; i++) {
    mscsound_device_t *newDevice = mscsound_create_device(i);
    mscsound_list_add_element((mscsound_list_t **)&(*((*devices)->output0)),
                              newDevice);
  }

  Pa_Terminate();
  return;
error:
  Pa_Terminate();
  fprintf(stderr, "An error occured while using the portaudio stream\n");
  fprintf(stderr, "Error number: %d\n", err);
  fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
  *((*devices)->output0) = NULL;
}

void mscsound_show_devices(mscsound_device_list_t **devices) {
  int deviceID = 0;

  strcpy(*((*devices)->output1), "");

  char *aux = calloc(200, sizeof(char));
  strcpy(aux, "");
  mscsound_list_t *temp1 = *((*devices)->output0);

  while (temp1) {
    // <= 20% free
    if (strlen(*((*devices)->output1)) >= (*devices)->lenOutput1 * 0.8) {
      (*devices)->lenOutput1 *= 1.4;
      *((*devices)->output1) =
          realloc(*((*devices)->output1), (*devices)->lenOutput1);
    }
    sprintf(aux, "--------------------------------------- device #%d ",
            deviceID);
    strcat(*((*devices)->output1), aux);
    mscsound_device_t *dev =
        (mscsound_device_t *)((mscsound_list_t *)temp1)->data;
    if (dev->defaultDisplayed == 0)
      strcat(*((*devices)->output1), "(Input)\n");
    else
      strcat(*((*devices)->output1), " (Output)\n");

    sprintf(aux, "name: %s\n", dev->deviceInfo->name);
    strcat(*((*devices)->output1), aux);

    sprintf(aux, "maxInputChannels: %d\n", dev->deviceInfo->maxInputChannels);
    strcat(*((*devices)->output1), aux);

    sprintf(aux, "maxOutputChannels: %d\n", dev->deviceInfo->maxOutputChannels);
    strcat(*((*devices)->output1), aux);

    sprintf(aux, "defaultSampleRate: %.2f\n",
            dev->deviceInfo->defaultSampleRate);
    strcat(*((*devices)->output1), aux);

    mscsound_list_t *temp2 = ((mscsound_list_t *)temp1)->next;
    temp1 = temp2;
    deviceID++;
  }
  strcat(*((*devices)->output1), "---------------------------------------\n");
  printf("%s", *((*devices)->output1));
  free(aux);
}
