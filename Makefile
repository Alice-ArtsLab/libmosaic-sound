CC := gcc
CFLAGS := -Wall -Werror -fPIC
LIBS := -lportaudio -lm `pkg-config --libs sndfile`
LIBDIR := src
LIB_NAME := mosaic-sound
LIB_VERSION := 1
BUILD := build
DIST := dist
OBJS :=	$(BUILD)/list.o \
        $(BUILD)/devices.o \
        $(BUILD)/whitenoise.o \
        $(BUILD)/audiomath.o \
        $(BUILD)/oscillators.o \
        $(BUILD)/mic.o \
        $(BUILD)/biquad.o \
        $(BUILD)/parametricequalizer.o \
        $(BUILD)/lowshelving.o \
        $(BUILD)/highshelving.o \
        $(BUILD)/playback.o \
		$(BUILD)/record.o

TARGET := $(OBJS) static
all: $(TARGET)

static:
	mkdir -p "$(DIST)"
	ar -crs $(DIST)/lib$(LIB_NAME).a $(OBJS)

# dynamic
.PHONY:	install
install:
	rm -rf "$(DIST)"
	mkdir -p "$(DIST)"
	$(CC) $(CFLAGS) -shared -o $(DIST)/lib$(LIB_NAME).so.$(LIB_VERSION) $(OBJS)
	ln -s lib$(LIB_NAME).so.$(LIB_VERSION) $(DIST)/lib$(LIB_NAME).so

	cp $(DIST)/lib$(LIB_NAME).so.$(LIB_VERSION) /usr/lib
	cp $(DIST)/lib$(LIB_NAME).so /usr/lib
	cp $(LIBDIR)/$(LIB_NAME).h /usr/include

.PHONY:	uninstall
unistall:
	rm -rf /usr/lib/lib$(LIB_NAME).so.$(LIB_VERSION)
	rm -rf /usr/lib/lib$(LIB_NAME).so
	rm -rf /usr/include/$(LIB_NAME).h

.PHONY: examples
examples:	install
	cd examples/ && $(MAKE)

.PHONY: clean
clean:
	rm -rf $(BUILD) $(DIST)

.PHONY: clean_examples
clean_examples:
	rm -rf examples/build examples/dist

$(BUILD)/list.o: $(LIBDIR)/util/list.c $(LIBDIR)/util/include/list.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/devices.o: $(LIBDIR)/modules/devices.c $(LIBDIR)/modules/include/devices.h $(LIBDIR)/util/include/list.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/whitenoise.o: $(LIBDIR)/modules/whitenoise.c $(LIBDIR)/modules/include/whitenoise.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/audiomath.o: $(LIBDIR)/modules/audiomath.c $(LIBDIR)/modules/include/audiomath.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/oscillators.o: $(LIBDIR)/modules/oscillators.c $(LIBDIR)/modules/include/oscillators.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/mic.o: $(LIBDIR)/modules/mic.c $(LIBDIR)/modules/include/mic.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/biquad.o: $(LIBDIR)/modules/biquad.c $(LIBDIR)/modules/include/biquad.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/parametricequalizer.o: $(LIBDIR)/modules/parametricequalizer.c $(LIBDIR)/modules/include/parametricequalizer.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/lowshelving.o: $(LIBDIR)/modules/lowshelving.c $(LIBDIR)/modules/include/lowshelving.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/highshelving.o: $(LIBDIR)/modules/highshelving.c $(LIBDIR)/modules/include/highshelving.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/playback.o: $(LIBDIR)/modules/playback.c $(LIBDIR)/modules/include/playback.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/record.o: $(LIBDIR)/modules/record.c $(LIBDIR)/modules/include/record.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
