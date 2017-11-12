CC := gcc
CFLAGS := -g -Wall
LIBS := -lportaudio -lm `pkg-config --libs sndfile`
SRC := src/
BUILD := build/
OBJSRC := ../build/
BIN := bin/
OBJS := $(OBJSRC)list.o \
        $(OBJSRC)devices.o \
        $(OBJSRC)whitenoise.o \
        $(OBJSRC)audiomath.o \
        $(OBJSRC)oscillators.o \
        $(OBJSRC)mic.o \
        $(OBJSRC)biquad.o \
        $(OBJSRC)parametricequalizer.o \
        $(OBJSRC)lowshelving.o \
        $(OBJSRC)highshelving.o \
        $(OBJSRC)playback.o \
		$(OBJSRC)record.o

TARGET := $(BIN)record_mic $(BIN)playback_mono $(BIN)playback_stereo \
		  $(BIN)osc_math $(BIN)noise $(BIN)devices $(BIN)allpass $(BIN)lowpass \
		  $(BIN)highpass $(BIN)bandpass $(BIN)bandreject $(BIN)parametric_eq \
		  $(BIN)lowshelving $(BIN)highshelving


all: $(TARGET)

# Example: record microphone
$(BIN)record_mic:	$(BUILD)record_mic.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)record_mic.o: $(SRC)record_mic.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: playback mono
$(BIN)playback_mono:	$(BUILD)playback_mono.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)playback_mono.o: $(SRC)playback_mono.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: playback stereo
$(BIN)playback_stereo:	$(BUILD)playback_stereo.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)playback_stereo.o: $(SRC)playback_stereo.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: sum of two oscillators
$(BIN)osc_math:	$(BUILD)osc_math.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)osc_math.o: $(SRC)osc_math.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: white noise
$(BIN)noise:	$(BUILD)noise.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)noise.o: $(SRC)noise.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: list devices
$(BIN)devices:	$(BUILD)devices.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)devices.o: $(SRC)devices.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: allpass
$(BIN)allpass:	$(BUILD)allpass.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)allpass.o: $(SRC)allpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: lowpass
$(BIN)lowpass:	$(BUILD)lowpass.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)lowpass.o: $(SRC)lowpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: highpass
$(BIN)highpass:	$(BUILD)highpass.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)highpass.o: $(SRC)highpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: bandpass
$(BIN)bandpass:	$(BUILD)bandpass.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)bandpass.o: $(SRC)bandpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: bandreject
$(BIN)bandreject:	$(BUILD)bandreject.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)bandreject.o: $(SRC)bandreject.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: parametric equalizer
$(BIN)parametric_eq:	$(BUILD)parametric_eq.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)parametric_eq.o: $(SRC)parametric_eq.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: lowshelving
$(BIN)lowshelving:	$(BUILD)lowshelving.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)lowshelving.o: $(SRC)lowshelving.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

# Example: highshelving
$(BIN)highshelving:	$(BUILD)highshelving.o $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)highshelving.o: $(SRC)highshelving.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@
