LIB=libmemdraw.a
CC=gcc
CFLAGS=-I../include -I. -c -ggdb -D_THREAD_SAFE -pthread
O=o

OFILES=\
	alloc.$O\
	arc.$O\
	cload.$O\
	cmap.$O\
	cread.$O\
	defont.$O\
	draw.$O\
	ellipse.$O\
	fillpoly.$O\
	hwdraw.$O\
	line.$O\
	load.$O\
	openmemsubfont.$O\
	poly.$O\
	read.$O\
	string.$O\
	subfont.$O\
	unload.$O\
	write.$O

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

