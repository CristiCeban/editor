OBJS = \
	editor.o \
	terminal_state.o 
BIN = editor
CFLAGS = -std=gnu99 -Wall -Werror

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -f  $(BIN) $(OBJS)