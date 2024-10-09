# Makefile for Slot Machine Project

CC = gcc               # The compiler to use
CFLAGS = -Wall          # Compiler flags to show all warnings

TARGET = build/slot_machine   # The output executable file

SRC = src/main.c        # The source code files

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
