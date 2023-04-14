CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-L. -lcodecA -lcodecB

all: encode decode

encode: encode.o
	$(CC) $(CFLAGS) -o $@ encode.o $(LDFLAGS)

decode: decode.o
	$(CC) $(CFLAGS) -o $@ decode.o $(LDFLAGS)

encode.o: encode.c
	$(CC) $(CFLAGS) -c -o $@ $<

decode.o: decode.c
	$(CC) $(CFLAGS) -c -o $@ $<

libcodecA.so: codecA.o
	$(CC) $(CFLAGS) -shared -o $@ $<

codecA.o: codecA.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

libcodecB.so: codecB.o
	$(CC) $(CFLAGS) -shared -o $@ $<

codecB.o: codecB.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

.PHONY: clean all

clean:
	rm -f *.o *.a *.so encode decode 