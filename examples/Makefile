CC := gcc
CFLAGS :=	-g -Wall
LIBS :=	-lportaudio -lm  -lasound -lpthread \
				`pkg-config --libs sndfile --cflags gtk+-3.0`
LIB_FLAGS :=  -I/usr/include/mosaic/mosaic-sound -lmosaic-sound
SRC :=	src/
BUILD :=	build/
BIN :=	bin/

TARGET := $(BIN)record_mic $(BIN)playback_mono $(BIN)playback_stereo \
		  $(BIN)osc_math $(BIN)whitenoise $(BIN)devices $(BIN)allpass $(BIN)lowpass \
		  $(BIN)highpass $(BIN)bandpass $(BIN)bandreject $(BIN)parametric_eq \
		  $(BIN)lowshelving $(BIN)highshelving $(BIN)channelshootersplitter \
			$(BIN)audiofloatmath $(BIN)vubar $(BIN)adsr $(BIN)midi $(BIN)volume


all: $(TARGET)

# Example: record microphone
$(BIN)record_mic:	$(BUILD)record_mic.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)record_mic.o: $(SRC)record_mic.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: playback mono
$(BIN)playback_mono:	$(BUILD)playback_mono.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)playback_mono.o: $(SRC)playback_mono.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: playback stereo
$(BIN)playback_stereo:	$(BUILD)playback_stereo.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)playback_stereo.o: $(SRC)playback_stereo.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: sum of two oscillators
$(BIN)osc_math:	$(BUILD)osc_math.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)osc_math.o: $(SRC)osc_math.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: whitenoise
$(BIN)whitenoise:	$(BUILD)whitenoise.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)whitenoise.o: $(SRC)whitenoise.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: list devices
$(BIN)devices:	$(BUILD)devices.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)devices.o: $(SRC)devices.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: allpass
$(BIN)allpass:	$(BUILD)allpass.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)allpass.o: $(SRC)allpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: lowpass
$(BIN)lowpass:	$(BUILD)lowpass.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)lowpass.o: $(SRC)lowpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: highpass
$(BIN)highpass:	$(BUILD)highpass.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)highpass.o: $(SRC)highpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: bandpass
$(BIN)bandpass:	$(BUILD)bandpass.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)bandpass.o: $(SRC)bandpass.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: bandreject
$(BIN)bandreject:	$(BUILD)bandreject.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)bandreject.o: $(SRC)bandreject.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: parametric equalizer
$(BIN)parametric_eq:	$(BUILD)parametric_eq.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)parametric_eq.o: $(SRC)parametric_eq.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: lowshelving
$(BIN)lowshelving:	$(BUILD)lowshelving.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)lowshelving.o: $(SRC)lowshelving.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: highshelving
$(BIN)highshelving:	$(BUILD)highshelving.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)highshelving.o: $(SRC)highshelving.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: channelshootersplitter
$(BIN)channelshootersplitter:	$(BUILD)channelshootersplitter.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)channelshootersplitter.o: $(SRC)channelshootersplitter.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: Change gain
$(BIN)audiofloatmath:	$(BUILD)audiofloatmath.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)audiofloatmath.o: $(SRC)audiofloatmath.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: VUBar
$(BIN)vubar:	$(BUILD)vubar.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)vubar.o: $(SRC)vubar.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: ADSR
$(BIN)adsr:	$(BUILD)adsr.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)adsr.o: $(SRC)adsr.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: MIDI
$(BIN)midi:	$(BUILD)midi.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)midi.o: $(SRC)midi.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)

# Example: VUBar
$(BIN)volume:	$(BUILD)volume.o
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ $(LIB_FLAGS) -o $@  $(LIBS)

$(BUILD)volume.o: $(SRC)volume.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< $(LIB_FLAGS) -o $@  $(LIBS)
