SOURCE	= main.c test_assert.c
HEADER	=
SRC_DIR = .
BUILD_DIR = build
OUT	= tests
CC	= gcc
FLAGS	= --std=gnu17 -g -Wall
LFLAGS	=

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE))

$(OUT): all
	./$(OUT)

all: $(OBJS)
	$(CC) -o $(OUT) $^ $(LFLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_DIR)
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(OUT)
	rmdir $(BUILD_DIR)

