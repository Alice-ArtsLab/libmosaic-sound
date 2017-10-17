typedef struct {
    int type; /*0: Allpass; 1: Lowpass; 2: Highpass; 3: Bandpass; 4: Bandreject*/
    int order; /*1: First-order; 2: Second-order*/
    float *input;
    float *output;
    int framesPerBuffer;
    float sampleRate;
    float slope;
    float cutOff;
    void (*process)(void *self);
}iir_t;

iir_t *create_iir(int type, int order, int framesPerBuffer);

void allpass_process();
void lowpass_process();
void highpass_process();
void bandpass_process();
void bandreject_process();
