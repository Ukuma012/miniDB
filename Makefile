CC = gcc
CFLAGS = -Wall -O2

SRCS = minidb.c tokenize.c
OBJS = $(SRCS:.c=.o)
TARGET = minidb

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
