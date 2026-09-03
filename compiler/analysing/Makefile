CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

SRCS = file_open_buffer.c string_char_processing.c scanner_helper.c tokenize.c analysis.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = analyzer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
