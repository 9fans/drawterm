LIB=libexportfs.a
CC=gcc
CFLAGS=-I../include -I. -I.. -c -ggdb -D_THREAD_SAFE -pthread
O=o

OFILES=\
	exportfs.$O\
	exportsrv.$O

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

