SOURCE	= main.c
HEADER	=
SRC_DIR = .
BUILD_DIR = build
OUT	= a.out
CC	= gcc
FLAGS	= --std=gnu17 -g -Wall
LFLAGS	=

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE))

all: $(OBJS)
	$(CC) -o $(OUT) $^ $(LFLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(OUT)
	rmdir $(BUILD_DIR)

