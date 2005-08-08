LIB=libdraw.a
CC=gcc
CFLAGS=-I../include -I. -c -ggdb -D_THREAD_SAFE -pthread
O=o

OFILES=\
	alloc.$O\
	arith.$O\
	bytesperline.$O\
	chan.$O\
	defont.$O\
	drawrepl.$O\
	icossin.$O\
	icossin2.$O\
	rectclip.$O\
	rgb.$O

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

