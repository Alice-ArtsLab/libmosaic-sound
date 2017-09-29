#include "general/include/devices.h"
// #include "soundsources/include/mic.h"
// #include "soundsources/include/oscillators.h"
// #include "soundsources/include/whitenoise.h"

int main(int argc, char *argv[]) {
  device_list_t *devices = create_devices();
  devices->process(devices);
  devices->show(devices);

  return 0;
}
