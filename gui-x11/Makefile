LIB=libx11.a
CC=gcc
CFLAGS=-I../include -I. -I/usr/X11R6/include -I../kern -c -ggdb -D_THREAD_SAFE -pthread
O=o

OFILES=\
	alloc.$O\
	cload.$O\
	draw.$O\
	load.$O\
	screen.$O\
	keysym2ucs-x11.$O

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

