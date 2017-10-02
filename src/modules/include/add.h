typedef struct {
    void (*process)(void *self);
    float * output;
    float * input1;
    float * input2;
    int framesPerBuffer;
}add_t;

add_t* create_add(int framesPerBuffer);
void add_process();
