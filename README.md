# Sound Design with *libmosaic-sound*

**This repository contains the library libmosaic-sound written in the 'C' programming language based on the PortAudio library. This library provides resources for working with Sound Design.**

-------------

## Implemented codes

There are the following implementations:

* ###  Audio Filter
    * All-pass
    * Bandpass
    * High-pass
    * Low-pass
    * High Shelving
    * Low Shelving
    * Parametric Equalizer

* ### Audio Math
    * Plus
    * Minus
    * Times
    * Divided by

* ### General
    * List audio devices

* ### Output
    * Buffer
    * File
    * Speaker

* ### Sound Sources
    * Oscillators
    * White Noise
    * Microphones
    * File / Buffer

## Solving Dependecies
`sudo apt-get install libsndfile1-dev`

`sudo apt-get install portaudio19-dev`

## Compiling and Installing the library

Compiling library: `make`

Installing library: `sudo make install`


## Compiling and Running the examples
Compiling examples: `sudo make examples`

Running: `./examples/bin/<filename>`

**Note:** We need to compile and install the library first.

## Cleaning the library and examples

Cleaning library: `sudo make clean`

Cleaning examples: `sudo make clean_examples`
