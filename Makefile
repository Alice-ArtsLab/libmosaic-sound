CC :=	gcc
CFLAGS :=	-g -fPIC #-g -Wall -Werror -fPIC
LIBS :=	-lportaudio -lm  -lasound -lpthread \
				`pkg-config --libs sndfile --cflags gtk+-3.0`
SRC :=	src
LIBDIR :=	/usr/include/mosaic/mosaic-sound
LIB_NAME :=	mosaic-sound
LIB_FLAGS :=  -I/usr/include/mosaic/mosaic-sound -lmosaic-sound
LIB_VERSION :=	1
BUILD :=	build
DIST :=	dist
OBJS :=	$(BUILD)/list.o $(BUILD)/devices.o $(BUILD)/whitenoise.o \
    	$(BUILD)/audiomath.o $(BUILD)/audiofloatmath.o $(BUILD)/oscillators.o \
    	$(BUILD)/mic.o $(BUILD)/biquad.o $(BUILD)/parametricequalizer.o \
    	$(BUILD)/lowshelving.o $(BUILD)/highshelving.o $(BUILD)/playback.o \
			$(BUILD)/record.o $(BUILD)/speaker.o $(BUILD)/channelshootersplitter.o \
			$(BUILD)/vubar.o $(BUILD)/adsr.o $(BUILD)/gui.o $(BUILD)/midi.o \
			$(BUILD)/volume.o $(BUILD)/grid.o

TARGET := $(OBJS) static
all: $(TARGET)

static:
	mkdir -p "$(DIST)"
	ar -crs $(DIST)/lib$(LIB_NAME).a $(OBJS)

# dynamic
.PHONY:	install
install:
	$(CC) $(CFLAGS) -shared -o $(DIST)/lib$(LIB_NAME).so.$(LIB_VERSION) $(OBJS)
	ln -s lib$(LIB_NAME).so.$(LIB_VERSION) $(DIST)/lib$(LIB_NAME).so
	rm -rf "$(LIBDIR)/include"
	mkdir -p "$(LIBDIR)/include"
	mv $(DIST)/lib$(LIB_NAME).so.$(LIB_VERSION) /usr/lib
	mv $(DIST)/lib$(LIB_NAME).so /usr/lib
	cp $(SRC)/$(LIB_NAME).h $(LIBDIR)
	cp $(SRC)/modules/include/*  $(LIBDIR)/include
	cp $(SRC)/GUI/include/*  $(LIBDIR)/include
	cp $(SRC)/util/include/*  $(LIBDIR)/include

.PHONY:	uninstall
uninstall:
	rm -rf /usr/lib/lib$(LIB_NAME).so.$(LIB_VERSION)
	rm -rf /usr/lib/lib$(LIB_NAME).so
	rm -rf $(LIBDIR)

.PHONY: examples
examples:
	cd examples/ && $(MAKE)

.PHONY: clean
clean:
	rm -rf $(BUILD) $(DIST)

.PHONY: clean_examples
clean_examples:
	rm -rf examples/build examples/bin

$(BUILD)/list.o: $(SRC)/util/list.c $(SRC)/util/include/list.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/devices.o: $(SRC)/modules/devices.c $(SRC)/modules/include/devices.h \
					$(SRC)/util/include/list.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/whitenoise.o: $(SRC)/modules/whitenoise.c \
					   $(SRC)/modules/include/whitenoise.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/audiomath.o: $(SRC)/modules/audiomath.c \
					  $(SRC)/modules/include/audiomath.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/audiofloatmath.o: $(SRC)/modules/audiofloatmath.c \
					  $(SRC)/modules/include/audiofloatmath.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/oscillators.o: $(SRC)/modules/oscillators.c \
						$(SRC)/modules/include/oscillators.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/mic.o: $(SRC)/modules/mic.c $(SRC)/modules/include/mic.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/biquad.o: $(SRC)/modules/biquad.c $(SRC)/modules/include/biquad.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/parametricequalizer.o: $(SRC)/modules/parametricequalizer.c \
								$(SRC)/modules/include/parametricequalizer.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/lowshelving.o: $(SRC)/modules/lowshelving.c \
						$(SRC)/modules/include/lowshelving.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/highshelving.o: $(SRC)/modules/highshelving.c \
						 $(SRC)/modules/include/highshelving.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/playback.o: $(SRC)/modules/playback.c $(SRC)/modules/include/playback.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/record.o: $(SRC)/modules/record.c $(SRC)/modules/include/record.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/speaker.o: $(SRC)/modules/speaker.c $(SRC)/modules/include/speaker.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/channelshootersplitter.o: $(SRC)/modules/channelshootersplitter.c \
													 $(SRC)/modules/include/channelshootersplitter.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/vubar.o: $(SRC)/GUI/vubar.c $(SRC)/GUI/include/vubar.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/adsr.o: $(SRC)/modules/adsr.c $(SRC)/modules/include/adsr.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/gui.o: $(SRC)/GUI/gui.c $(SRC)/GUI/include/gui.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/midi.o: $(SRC)/modules/midi.c $(SRC)/modules/include/midi.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/volume.o: $(SRC)/GUI/volume.c $(SRC)/GUI/include/volume.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD)/grid.o: $(SRC)/GUI/grid.c $(SRC)/GUI/include/grid.h
	mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
