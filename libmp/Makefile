# N.B.  This is used only for secstore.  It needn't be fast.

LIB=libmp.a
CC=gcc
CFLAGS=-I../include -I. -c -ggdb -D_THREAD_SAFE -pthread
O=o

OFILES=\
	betomp.$O\
	crt.$O\
	letomp.$O\
	mpadd.$O\
	mpaux.$O\
	mpcmp.$O\
	mpdigdiv.$O\
	mpdiv.$O\
	mpeuclid.$O\
	mpexp.$O\
	mpextendedgcd.$O\
	mpfmt.$O\
	mpinvert.$O\
	mpleft.$O\
	mpmod.$O\
	mpmul.$O\
	mprand.$O\
	mpright.$O\
	mpsub.$O\
	mptobe.$O\
	mptoi.$O\
	mptole.$O\
	mptoui.$O\
	mptouv.$O\
	mptov.$O\
	mpvecadd.$O\
	mpveccmp.$O\
	mpvecdigmuladd.$O\
	mpvecsub.$O\
	strtomp.$O

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

