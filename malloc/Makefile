CC = gcc
CPPFLAGS = -D_DEFAULT_SOURCE
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla -fvisibility=hidden -fPIC
LDFLAGS = -shared -Wl,-no-undefined

SRC = src/malloc.c
OBJ = $(SRC:.c=.o)
TARGET = libmalloc.so

all: library

library: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

check: $(TARGET)
	$(CC) -Wall -Wextra tests/test.c -o tests/test
	LD_PRELOAD=./$(TARGET) ./tests/test



clean:
	rm -f $(TARGET) $(OBJ) tests/test

.PHONY: all library check clean