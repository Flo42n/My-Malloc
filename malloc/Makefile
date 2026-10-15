CC = gcc
CPPFLAGS = -D_DEFAULT_SOURCE
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla -fvisibility=hidden -fPIC
LDFLAGS = -shared -Wl,--no-undefined

SRC = src/malloc.c
OBJ = $(SRC:.c=.o)
TARGET = libmalloc.so

all: library

library: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

check: library tests/test
	LD_PRELOAD=./$(TARGET) ./tests/test	
	sh tests/test.sh

debug: clean
debug: CFLAGS += -g 
debug: library

tests/%: tests/%.c
	$(CC) -std=c11 -D_DEFAULT_SOURCE -Wall -Wextra -Werror -pthread -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ) tests/test *.o

.PHONY: all library check clean debug
