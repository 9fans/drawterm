LIB=libkern.a
CC=gcc
CFLAGS=-I../include -I. -c -ggdb -D_THREAD_SAFE -pthread
O=o
#CC=cl
#CFLAGS=-c -nologo -W3 -YX -Zi -MT -Zl -I../include -DWINDOWS
#O=obj

OFILES=\
	allocb.$O\
	cache.$O\
	chan.$O\
	data.$O\
	dev.$O\
	devcons.$O\
	devdraw.$O\
	devfs.$O\
	devip.$O\
	devip-posix.$O\
	devmnt.$O\
	devmouse.$O\
	devpipe.$O\
	devroot.$O\
	devssl.$O\
	devtab.$O\
	error.$O\
	parse.$O\
	pgrp.$O\
	posix.$O\
	procinit.$O\
	rwlock.$O\
	sleep.$O\
	smalloc.$O\
	stub.$O\
	sysfile.$O\
	sysproc.$O\
	qio.$O\
	qlock.$O\
	term.$O\
	todo.$O\
	uart.$O\
	waserror.$O

$(LIB): $(OFILES)
	ar r $(LIB) $(OFILES)
	ranlib $(LIB)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

