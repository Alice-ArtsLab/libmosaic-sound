CC := gcc
CFLAGS := -g -Wall
LIBS := -lportaudio -lm `pkg-config --libs sndfile`
SRC := src
BUILD := build/
BIN := bin/
OBJS := $(BUILD)main.o \
        $(BUILD)list.o \
        $(BUILD)devices.o \
        $(BUILD)whitenoise.o \
        $(BUILD)audiomath.o \
        $(BUILD)oscillators.o \
        $(BUILD)mic.o \
        $(BUILD)biquad.o \
        $(BUILD)parametricequalizer.o \
        $(BUILD)lowshelving.o \
        $(BUILD)highshelving.o \
        $(BUILD)playback.o \
		$(BUILD)playback.o

TARGET := $(BIN)main
all: $(TARGET)

$(BIN)main: $(OBJS)
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD)main.o: $(SRC)/main.c
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)list.o: $(SRC)/util/list.c $(SRC)/util/include/list.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)devices.o: $(SRC)/modules/devices.c $(SRC)/modules/include/devices.h $(SRC)/util/include/list.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)whitenoise.o: $(SRC)/modules/whitenoise.c $(SRC)/modules/include/whitenoise.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)audiomath.o: $(SRC)/modules/audiomath.c $(SRC)/modules/include/audiomath.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)oscillators.o: $(SRC)/modules/oscillators.c $(SRC)/modules/include/oscillators.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)mic.o: $(SRC)/modules/mic.c $(SRC)/modules/include/mic.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)biquad.o: $(SRC)/modules/biquad.c $(SRC)/modules/include/biquad.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)parametricequalizer.o: $(SRC)/modules/parametricequalizer.c $(SRC)/modules/include/parametricequalizer.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)lowshelving.o: $(SRC)/modules/lowshelving.c $(SRC)/modules/include/lowshelving.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)highshelving.o: $(SRC)/modules/highshelving.c $(SRC)/modules/include/highshelving.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)playback.o: $(SRC)/modules/playback.c $(SRC)/modules/include/playback.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)record.o: $(SRC)/modules/record.c $(SRC)/modules/include/record.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) $(BIN)
