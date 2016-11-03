CC = gcc
CFLAGS = -Wall
LFLAGS =
OBJECTS = $(patsubst .c,%.o,$(wildcard srs/*.c))
EXEC = tp2

$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(EXEC)

data:
	git submodule init
	git submodule update
