LIB=libmemlayer.a
CC=gcc
CFLAGS=-I../include -I. -c -ggdb -D_THREAD_SAFE -pthread
O=o

OFILES=\
	draw.$O\
	lalloc.$O\
	layerop.$O\
	ldelete.$O\
	lhide.$O\
	line.$O\
	load.$O\
	lorigin.$O\
	lsetrefresh.$O\
	ltofront.$O\
	ltorear.$O\
	unload.$O

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

