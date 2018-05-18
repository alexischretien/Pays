CC = gcc
CFLAGS = -Wall `pkg-config --cflags jansson`
LFLAGS = `pkg-config --libs jansson`
OBJECTS = $(patsubst %.c,%.o,$(wildcard src/*.c))
FICHIERS = $(wildcard bin/*.txt) $(wildcard bin/*.dot) $(wildcard bin/*.png)

EXEC = bin/run

$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean data test

clean:
	rm -f $(OBJECTS) $(EXEC) $(FICHIERS)

data:
	git submodule init
	git submodule update
	cd data/countries; git checkout master 
	cd data/countries; git pull

test: 
	cd test; bats suite1.bats suite2.bats suite3.bats

