ROOT=..
include ../Make.config
LIB=../libmachdep.a

OFILES=\
	getcallerpc.$O\
	tas.$O

default: $(LIB)
$(LIB): $(OFILES)
	$(AR) r $(LIB) $(OFILES)
	$(RANLIB) $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

