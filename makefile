OBJS = \
	editor.o \
	terminal_handler.o \
	file_handler.o \
	events_handler.o \
	display_handler.o 
BIN = editor
CFLAGS = -std=gnu99 -Wall -Werror

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f $(OBJS)