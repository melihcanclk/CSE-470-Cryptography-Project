# tool macros
CXX := gcc
CXXFLAGS :=
DBGFLAGS := -g
CCOBJFLAGS := $(CXXFLAGS) -c

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := .
DBG_PATH := debug

# compile macros
TARGET_NAME := main
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST)

# default rule
default: makedir all

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

all: makedir xoodyak_hash xoodyak_keyed

xoodyak_hash: xoodyak_hash.o xoodyak_cycle.o
	$(CC) -o xoodyak_hash xoodyak_hash.o xoodyak_cycle.o

xoodyak_keyed: xoodyak_keyed.o xoodyak_cycle.o
	$(CC) -o xoodyak_keyed xoodyak_keyed.o xoodyak_cycle.o

xoodyak_hash.o: 
	$(CC) -c xoodyak_hash.c -o xoodyak_hash.o

xoodyak_keyed.o: 
	$(CC) -c xoodyak_keyed.c -o xoodyak_keyed.o

xoodyak_cycle.o: 
	$(CC) -c xoodyak_cycle.c -o xoodyak_cycle.o


.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean_keyed
clean:
	rm -f *.o xoodyak_keyed xoodyak_hash
	rmdir --ignore-fail-on-non-empty $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)


.PHONY: distclean
distclean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)
	
	