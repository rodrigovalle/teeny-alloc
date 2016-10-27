CC=gcc
CFLAGS=-O2 -ggdb
WARN=-Winline -Wall -pedantic

test: teenyalloc.h test/teenyalloc_debug.h test/smoke_test.c
	$(CC) $(CFLAGS) $(WARN) -DDEBUG test/smoke_test.c

test2: teenyalloc.h test/teenyalloc_debug.h test/smoke_test2.c
	$(CC) $(CFLAGS) $(WARN) -DDEBUG test/smoke_test2.c

speedtest: teenyalloc.h test/speed_test.c
	$(CC) $(CFLAGS) $(WARN) -Wno-unused-but-set-variable test/speed_test.c

clean:
	rm -rf a.out

.PHONY: clean
