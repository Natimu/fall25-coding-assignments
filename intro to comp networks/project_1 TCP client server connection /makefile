# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Target executable name
TARGET = client

# Source files
SRC = client.c

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build artifacts
clean:
	rm -f $(TARGET)
