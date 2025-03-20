CC = g++
CFLAGS = -Iinclude -Isrc/types -Isrc/utils -Wall -Wextra -g
SRC = src/main.cpp src/traceroute.cpp src/utils/network_utils.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = network-utility
TESTS = tests/test_main.cpp tests/test_traceroute.cpp tests/test_network_utils.cpp
TEST_OBJ = $(TESTS:.cpp=.o)
TEST_TARGET = test_network_utility

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $(TEST_TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_OBJ) $(TEST_TARGET)

.PHONY: all clean test