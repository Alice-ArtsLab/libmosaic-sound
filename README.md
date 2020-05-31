# Sound Design with *libmosaic-sound*

**This repository contains the library libmosaic-sound written in the 'C'
programming language based on the PortAudio API. This library provides resources
for working with Sound Design.**

-------------

## Implemented codes

There are the following implementations organized by module and group name:

```
    src/modules/
    ├── gui
    │   ├── general
    │   │   ├── grid.c
    │   │   ├── gui.c
    │   │   └── include
    │   │       ├── grid.h
    │   │       └── gui.h
    │   ├── input
    │   │   ├── include
    │   │   │   └── volume.h
    │   │   └── volume.c
    │   └── output
    │       ├── include
    │       │   ├── vubar.h
    │       │   └── waveform.h
    │       ├── vubar.c
    │       └── waveform.c
    ├── midi
    │   └── device
    │       ├── include
    │       │   └── midi.h
    │       └── midi.c
    ├── sound
    │   ├── audiofloatmath
    │   │   ├── audiofloatmath.c
    │   │   └── include
    │   │       └── audiofloatmath.h
    │   ├── audiomath
    │   │   ├── audiomath.c
    │   │   └── include
    │   │       └── audiomath.h
    │   ├── audiosource
    │   │   ├── include
    │   │   │   ├── oscillators.h
    │   │   │   └── whitenoise.h
    │   │   ├── oscillators.c
    │   │   └── whitenoise.c
    │   ├── conversion
    │   │   ├── include
    │   │   │   └── rms.h
    │   │   └── rms.c
    │   ├── envelope
    │   │   ├── adsr.c
    │   │   └── include
    │   │       └── adsr.h
    │   ├── filter
    │   │   ├── biquad.c
    │   │   ├── highshelving.c
    │   │   ├── include
    │   │   │   ├── biquad.h
    │   │   │   ├── highshelving.h
    │   │   │   ├── lowshelving.h
    │   │   │   └── parametricequalizer.h
    │   │   ├── lowshelving.c
    │   │   └── parametricequalizer.c
    │   ├── fx
    │   │   ├── delay.c
    │   │   └── include
    │   │       └── delay.h
    │   ├── general
    │   │   ├── channelshootersplitter.c
    │   │   ├── devices.c
    │   │   └── include
    │   │       ├── channelshootersplitter.h
    │   │       └── devices.h
    │   ├── input
    │   │   ├── include
    │   │   │   ├── mic.h
    │   │   │   └── playback.h
    │   │   ├── mic.c
    │   │   └── playback.c
    │   └── output
    │       ├── include
    │       │   ├── record.h
    │       │   └── speaker.h
    │       ├── record.c
    │       └── speaker.c
    └── util
        └── list
            ├── include
            │   └── list.h
            └── list.c

    34 directories, 48 files
```

## Solving Dependecies
`sudo apt-get install libsndfile1-dev`

`sudo apt-get install portaudio19-dev`

## Compiling and Installing the library

Compiling library: `$ make`

Installing library: `$ sudo make install`


## Compiling and Running the examples
Compiling examples: `$ make examples`

Running:

```
$ cd examples/bin/<group_name>
$ ./<filename>
```

**Note:** We need to compile and install the library first.

## Cleaning the library and examples

Cleaning library: `$ make clean`

Cleaning examples: `$ make clean_examples`

## Uninstalling

Terminal: `$ sudo make uninstall`
