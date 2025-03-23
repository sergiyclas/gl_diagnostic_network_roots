CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
INC_DIR = src
BUILD_DIR = build
TARGET = traceroute

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(wildcard $(INC_DIR)/*.h)

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJS) -o $(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
