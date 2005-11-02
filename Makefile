ROOT=.

include Make.config

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
	gui-$(GUI)/libgui.a\
	libmemdraw/libmemdraw.a\
	libdraw/libdraw.a\
	kern/libkern.a\
	libc/libc.a\
	libmemdraw/libmemdraw.a\
	libmemlayer/libmemlayer.a\
	libdraw/libdraw.a\
	libmachdep.a

$(TARG): $(OFILES) $(LIBS)
	$(CC) $(LDFLAGS) -o $(TARG) $(OFILES) $(LIBS) $(LDADD)

%.$O: %.c
	$(CC) $(CFLAGS) $*.c

clean:
	rm -f *.o */*.o */*.a *.a drawterm drawterm.exe

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

gui-$(GUI)/libgui.a:
	(cd gui-$(GUI); make)

