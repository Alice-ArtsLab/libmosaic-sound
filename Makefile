CC :=	gcc
CFLAGS :=	-g -Wall -Werror -fPIC
LIBS :=	-lportaudio -lm -lrt -lasound -ljack -lpthread \
				`pkg-config --libs sndfile --cflags gtk+-3.0`
MODULES_DIR := src/modules
BUILD :=	build
DIST :=	dist
SRC := src
LIB_DIR :=	/usr/include/mosaic/mosaic-sound
LIB_NAME :=	mosaic-sound
LIB_FLAGS :=  -I/usr/include/mosaic/mosaic-sound -lmosaic-sound
LIB_VERSION :=	1

# <full_path>/<filename>.c
SRCS :=	$(wildcard $(MODULES_DIR)/*/*/*.c)

# $(BUILD)/<module_name>/<group>/<obj_name>.o
OBJS :=	$(subst .c,.o,$(SRCS))
OBJS :=	$(subst $(MODULES_DIR)/,$(BUILD)/,$(OBJS))

# <module_name>/<group>/<obj_name>
MODULE_GROUP_OBJ :=	$(subst .c,,$(SRCS))
MODULE_GROUP_OBJ :=	$(subst $(MODULES_DIR)/,,$(MODULE_GROUP_OBJ))
OBJS_DIR := $(wildcard $(MODULES_DIR)/*/*)

# <module_name>/<group>
MODULES := $(subst $(MODULES_DIR)/,,$(OBJS_DIR))

# $(BUILD)/<module_name>/<group>
OBJS_DIR := $(subst $(MODULES_DIR)/,$(BUILD)/,$(OBJS_DIR))

TARGET := $(MODULE_GROUP_OBJ) static
all: $(TARGET)

$(MODULE_GROUP_OBJ):
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(MODULES_DIR)/$@.c -o $(BUILD)/$@.o $(LIBS)

.PHONY:	static
static:
	mkdir -p "$(DIST)"
	ar -crs $(DIST)/lib$(LIB_NAME).a $(OBJS)

# dynamic
.PHONY:	install
install:
	$(CC) $(CFLAGS) -shared -o $(DIST)/lib$(LIB_NAME).so.$(LIB_VERSION) $(OBJS)
	ln -s lib$(LIB_NAME).so.$(LIB_VERSION) $(DIST)/lib$(LIB_NAME).so
	rm -rf "$(LIB_DIR)/include"
	mkdir -p "$(LIB_DIR)/include"
	mv $(DIST)/lib$(LIB_NAME).so.$(LIB_VERSION) /usr/lib
	mv $(DIST)/lib$(LIB_NAME).so /usr/lib
	cp $(SRC)/$(LIB_NAME).h $(LIB_DIR)
	for name in $(MODULES); do \
  		cp src/modules/$$name/include/*  $(LIB_DIR)/include; \
  	done

.PHONY:	uninstall
uninstall:
	rm -rf /usr/lib/lib$(LIB_NAME).so.$(LIB_VERSION)
	rm -rf /usr/lib/lib$(LIB_NAME).so
	rm -rf $(LIB_DIR)

.PHONY: examples
examples:
	cd examples/ && $(MAKE)

.PHONY: clean
clean:
	rm -rf $(BUILD) $(DIST)

.PHONY: clean_examples
clean_examples:
	rm -rf examples/build examples/bin
