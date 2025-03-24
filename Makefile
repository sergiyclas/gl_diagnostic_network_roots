# Makefile for Linux-only build

PKG_NAME := rooter
PKG_VERSION := 1.0
PKG_RELEASE := 1

SRC_DIR := src
INC_DIR := src
BUILD_DIR := build
TARGET := rooter
TITLE:=Utility for testing root to host throught ICMP packets

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(wildcard $(INC_DIR)/*.h)

CC := gcc
CFLAGS := -Wall -g -I$(INC_DIR) -D_DEFAULT_SOURCE
LDFLAGS :=

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
