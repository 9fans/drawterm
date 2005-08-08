TARG=drawterm
CC=gcc
CFLAGS=-Iinclude -c -ggdb -D_THREAD_SAFE -pthread # not ready for this yet: -Wall
O=o
#CC=cl
#CFLAGS=-c -nologo -W3 -YX -Zi -MT -Zl -Iinclude -DWINDOWS
#O=obj

OFILES=\
	main.$O\
	cpu.$O\
	readcons.$O\
	secstore.$O\
    latin1.$O\

LIBS=\
	kern/libkern.a\
	exportfs/libexportfs.a\
	libauthsrv/libauthsrv.a\
	libsec/libsec.a\
	libmp/libmp.a\
	libmemdraw/libmemdraw.a\
	libmemlayer/libmemlayer.a\
	libdraw/libdraw.a\
	libc/libc.a\
	kern/libkern.a\
	gui-x11/libx11.a\
	libmemdraw/libmemdraw.a\
	libdraw/libdraw.a\
	kern/libkern.a\
	libc/libc.a\
	libmemdraw/libmemdraw.a\
	libmemlayer/libmemlayer.a\
	libdraw/libdraw.a\
	libmachdep.a

$(TARG): $(OFILES) $(LIBS)
	$(CC) -pthread -o $(TARG) $(OFILES) $(LIBS) -L/usr/X11R6/lib -lX11 -ggdb

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

clean:
	rm -f *.o */*.o */*.a drawterm  *.a

kern/libkern.a:
	(cd kern; make)

exportfs/libexportfs.a:
	(cd exportfs; make)

libauthsrv/libauthsrv.a:
	(cd libauthsrv; make)

libmp/libmp.a:
	(cd libmp; make)

libsec/libsec.a:
	(cd libsec; make)

libmemdraw/libmemdraw.a:
	(cd libmemdraw; make)

libmemlayer/libmemlayer.a:
	(cd libmemlayer; make)

libdraw/libdraw.a:
	(cd libdraw; make)

libc/libc.a:
	(cd libc; make)

gui-x11/libx11.a:
	(cd gui-x11; make)

#libmachdep.a:
#	arch=`uname -m|sed 's/i.86/386/;s/Power Macintosh/power/'`; \
#	(cd gcc$$arch &&  make)

libmachdep.a:
	(cd posix-386; make)

