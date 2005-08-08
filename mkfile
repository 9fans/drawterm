#CONF=FreeBSD
#CONF=FreeBSD-power	# MAC OSX
#CONF=Irix
CONF=posix
#CONF=OSF1
#CONF=Solaris
#CONF=Solaris-386
#CONF=Solaris-sparc
#CONF=Windows

<mkfile-$CONF
TARG=drawterm

OFILES=\
	main.$O\
	cpu.$O\
	readcons.$O\
	secstore.$O

DIRS=	kern exportfs libauthsrv libsec libmp libmemdraw libmemlayer libdraw libc
LIBS=\
	kern/libkern.$L\
	exportfs/libexportfs.$L\
	libauthsrv/libauthsrv.$L\
	libsec/libsec.$L\
	libmp/libmp.$L\
	libmemdraw/libmemdraw.$L\
	libmemlayer/libmemlayer.$L\
	libdraw/libdraw.$L\
	libc/libc.$L\
	$SYS-$objtype/libmachdep.$L \
	gui-win32/libgui.$L\
#	gui-x11/libx11.$L\

$TARG: $OFILES $LIBS
	$LD $LDFLAGS $prereq $OSLIBS 

# $TARG: $OFILES $LIBS
#	$CC -o $TARG $OFILES $LIBS $LDFLAGS

%.$O: %.c
	$CC $CFLAGS $stem.c

clean:
	rm -f *.$O */*.$O */*.$L drawterm  *.$L

#$LIBS:
#	for (i in $DIRS) {
#		cd $i
#		mk
#	}

kern/libkern.$L:
	cd kern; mk

exportfs/libexportfs.$L:
	cd exportfs; mk

libauthsrv/libauthsrv.$L:
	cd libauthsrv; mk

libmp/libmp.$L:
	cd libmp; mk

libsec/libsec.$L:
	cd libsec; mk

libmemdraw/libmemdraw.$L:
	cd libmemdraw; mk

libmemlayer/libmemlayer.$L:
	cd libmemlayer; mk

libdraw/libdraw.$L:
	cd libdraw; mk

libc/libc.$L:
	cd libc; mk

gui-x11/libx11.$L:
	cd gui-x11; mk

gui-win32/libgui.$L:
	cd gui-win32; mk

drawterm.res:\
	drawterm.ico\

$SYS-$objtype/libmachdep.$L:
	arch=$SYS-$objtype
	cd $arch; mk

#libmachdep.$L:
#	arch=`{uname -m|sed 's/i.86/386/;s/Power Macintosh/power/'}
#	cd gcc$$arch mk
