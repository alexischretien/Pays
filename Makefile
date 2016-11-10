CC = gcc
CFLAGS = -Wall
LFLAGS =
OBJECTS = $(patsubst .c,%.o,$(wildcard srs/*.c))
IMAGES = $(patsubs .png,.dot)
EXEC = tp2

$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS) -ljansson

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -ljansson 

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(EXEC) $(IMAGES)

data:
	git submodule init
	git submodule update
