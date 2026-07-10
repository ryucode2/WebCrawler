CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c17 -Iinclude

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

TARGET = $(BIN_DIR)/crawler

SOURCES = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


all: $(TARGET)


$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -lcurl -o $@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)


run: $(TARGET)
	./$(TARGET) https://example.com


.PHONY: all clean run
