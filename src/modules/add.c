#include <stdio.h>
#include <stdlib.h>
#include "include/add.h"

add_t* create_add(int framesPerBuffer) {
  add_t* add = malloc(sizeof(add_t));
  add->process = add_connect;
  add->framesPerBuffer = framesPerBuffer;
  add->output = NULL;
  return add;
}

void add_connect(add_t* add) {
  add->output = add->input1;
  add->process = add_process;
  add->process(add);
}

void add_process(add_t* add) {
  for (int i = 0; i < add->framesPerBuffer; i++) {
    add->output[i] = add->input1[i] + add->input2[i];
  }
}
