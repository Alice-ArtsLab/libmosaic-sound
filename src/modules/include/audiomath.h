#ifndef AUDIOMATH_H
#define AUDIOMATH_H

    typedef struct {
        float * output;
        float * input1;
        float * input2;
        int framesPerBuffer;
        void (*process)(void *self);
    }math_t;

    math_t* create_math(int framesPerBuffer, void (*function));

    void add_2freq(math_t *self);
    void sub_2freq(math_t *self);
    void mul_2freq(math_t *self);
    void div_2freq(math_t *self);

    void add_freq_float(math_t *self);
    void sub_freq_float(math_t *self);
    void mul_freq_float(math_t *self);
    void div_freq_float(math_t *self);

#endif /* audiomath.h */
