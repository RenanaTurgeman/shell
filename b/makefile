CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS = -L. -lcodecA -lcodecB

all: encode decode

encode: encode.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

decode: decode.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

libcodecA.so: codecA.c codecA.h
	$(CC) $(CFLAGS) -shared -o $@ codecA.c

libcodecB.so: codecB.c codecB.h
	$(CC) $(CFLAGS) -shared -o $@ codecB.c

clean:
	rm -f encode decode libcodecA.so libcodecB.so
