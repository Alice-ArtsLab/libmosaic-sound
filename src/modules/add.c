#include <stdio.h>
#include <stdlib.h>
#include "include/add.h"

add_t* create_add(int framesPerBuffer) {
  add_t* add = malloc(sizeof(add_t));
  add->process = add_process;
  add->framesPerBuffer = framesPerBuffer;
  add->output = malloc(framesPerBuffer * sizeof(float));
  return add;
}

void add_process(add_t* add) {
  for (int i = 0; i < add->framesPerBuffer; i++) {
    add->output[i] = add->input1[i] + add->input2[i];
  }
}
