#include "general/include/devices.h"
// #include "soundsources/include/mic.h"
// #include "soundsources/include/oscillators.h"
// #include "soundsources/include/whitenoise.h"

int main(int argc, char *argv[]){
    devices_t * devices = create_devices();
    devices->process(devices);
    devices->show(devices);

    return 0;
}
