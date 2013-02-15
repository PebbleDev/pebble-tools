CC=gcc
CFLAGS=-Wall -I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

appinfo: appinfo.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	@rm *.o appinfo

.PHONY: clean