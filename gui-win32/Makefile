ROOT=..
include ../Make.config
LIB=libgui.a

OFILES=\
	alloc.$O\
	cload.$O\
	draw.$O\
	load.$O\
	screen.$O\
	wstrtoutf.$O

default: $(LIB)
$(LIB): $(OFILES)
	$(AR) r $(LIB) $(OFILES)
	$(RANLIB) $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

