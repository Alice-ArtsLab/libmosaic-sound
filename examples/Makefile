CC := gcc
CFLAGS :=	-g -Wall
LIBS :=	-lportaudio -lm -lrt -lasound -ljack -lpthread \
				`pkg-config --libs sndfile --cflags gtk+-3.0`
LIB_FLAGS :=  -I/usr/include/mosaic/mosaic-sound -lmosaic-sound
SRC :=	src
BUILD :=	build
BIN :=	bin
# <full_path>/<filename>.c
SRCS :=	$(wildcard $(SRC)/*/*.c)
# <module_name>/<obj_name>
OBJ_MODULES :=	$(subst .c,,$(SRCS))
OBJ_MODULES :=	$(subst $(SRC)/,,$(OBJ_MODULES))
# <module_name>
MODULES := $(wildcard $(SRC)/*)
MODULES := $(subst $(SRC)/,,$(MODULES))

all: $(OBJ_MODULES)

$(OBJ_MODULES):
	for name in $(MODULES); do \
  	mkdir -p $(SRC)/$$name/$(BIN)/ \
		mkdir -p $(SRC)/$$name/$(BUILD)/; \
	done
	rm -rf mkdir
	$(CC) $(CFLAGS) -c $(SRC)/$@.c $(LIB_FLAGS) -o $(SRC)/$(subst /,/$(BUILD)/,$@).o $(LIBS)
	$(CC) $(CFLAGS) $(SRC)/$@.c $(LIB_FLAGS) -o $(SRC)/$(subst /,/$(BIN)/,$@)  $(LIBS)

.PHONY: clean
clean:

	for name in $(MODULES); do \
  	rm -rf $(SRC)/$$name/$(BIN)/ \
		rm -rf $(SRC)/$$name/$(BUILD)/; \
	done
