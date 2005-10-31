ROOT=..
include ../Make.config
LIB=../libmachdep.a

OFILES=\
	getcallerpc.$O\
	tas.$O

$(LIB): $(OFILES)
	$(AR) r $(LIB) $(OFILES)
	$(RANLIB) $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

