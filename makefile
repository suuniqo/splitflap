
### variables ###

debug ?= 0
NAME := splitflap
SRC_DIR := src
BUILD_DIR := build
TESTS_DIR := tests
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRCS))


### compiler ###

CC := gcc
CFLAGS := -Wall -Wextra -pedantic

ifeq ($(debug), 1)
	CFLAGS += -g -O0
else
	CFLAGS += $(CFLAGS) -O3
endif


### targets ###

## src ##

all: dir $(NAME)

$(NAME): $(OBJS) dir
	@$(CC) $(CFLAGS) $(OBJS) -o $(BIN_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c dir
	@$(CC) $(CFLAGS) -c $< -o $@

## sorter ##

sorter: dir
	@$(CC) $(CFLAGS) src/charset/alphabet.c src/error/die.c sorter/wordsorter.c -o $(BIN_DIR)/$@


### directory opts ###

dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)
	@rsync -a --include '*/' --exclude '*' $(SRC_DIR)/ $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
