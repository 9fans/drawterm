ROOT=.

include Make.config

OFILES=\
	main.$O\
	cpu.$O\
	readcons.$O\
	secstore.$O\
	latin1.$O\
	$(OS)-factotum.$O\

LIBS1=\
	kern/libkern.a\
	exportfs/libexportfs.a\
	libauth/libauth.a\
	libauthsrv/libauthsrv.a\
	libsec/libsec.a\
	libmp/libmp.a\
	libmemdraw/libmemdraw.a\
	libmemlayer/libmemlayer.a\
	libdraw/libdraw.a\
	gui-$(GUI)/libgui.a\
	libc/libc.a\

# stupid gcc
LIBS=$(LIBS1) $(LIBS1) $(LIBS1) libmachdep.a

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

libauth/libauth.a:
	(cd libauth; make)
	
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

