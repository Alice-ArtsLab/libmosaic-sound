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

## Compiling

Compiling library: `make`

Compiling examples: `make examples`

**Note:** We need to compile the library first.

Cleaning library: `make clean`

Cleaning examples: `make clean_examples`

## Running

Main: `./bin/main`

Examples: `./examples/bin/<filename>`
