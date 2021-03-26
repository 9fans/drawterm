[![Build Status](https://travis-ci.org/9fans/drawterm.svg?branch=master)](https://travis-ci.org/9fans/drawterm)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/9fans-drawterm/badge.svg)](https://scan.coverity.com/projects/9fans-drawterm)

INSTALLATION
--------------
To build on Unix, run CONF=unix make.

To build on Solaris using Sun cc, run CONF=sun make.

To build on Windows, you need Mingw.  See http://www.mingw.org.
Edit Make.config to uncomment the Windows section
and comment out the rest.  Then run CONF=win32 make.

(You can download nmake from 
http://support.microsoft.com/default.aspx?scid=kb;en-us;Q132084
Rename it to make.exe and put it in your path somewhere.
)

I haven't tested the Windows build on Windows itself.
I cross-compile using mingw32 on Linux.


SOURCE
------
Use Git: git clone https://github.com/9fans/drawterm
In the Plan 9 distribution: /sys/src/cmd/unix/drawterm/ (sometimes out of date)


HELP
----
Issue tracker: https://github.com/9fans/drawterm/issues


TO DO:
------

- Should import latest /dev/draw to allow resize of window

- Should copy 9term code and make console window a real
	9term window instead.

- Should implement /dev/label.



