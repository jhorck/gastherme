PROJ=gastherme
CC=gcc
SRC=gastherme.c
LIBS=-lmosquitto
CFLAGS=

all:
	$(CC) $(SRC) $(LIBS) $(CFLAGS) -o $(PROJ)

clean:
	rm $(PROJ)
