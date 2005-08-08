LIB=libauthsrv.a
CC=gcc
CFLAGS=-I../include -I. -c -ggdb -D_THREAD_SAFE -pthread
O=o

OFILES=\
	_asgetticket.$O\
	_asrdresp.$O\
	convA2M.$O\
	convM2A.$O\
	convM2PR.$O\
	convM2T.$O\
	convM2TR.$O\
	convPR2M.$O\
	convT2M.$O\
	convTR2M.$O\
	nvcsum.$O\
	opasstokey.$O\
	passtokey.$O\
	readnvram.$O\

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

