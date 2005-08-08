#if defined(linux) || defined(IRIX) || defined(SOLARIS) || defined(OSF1) || defined(__FreeBSD__) || defined(__APPLE__)
#	include "unix.h"
#	ifdef __APPLE__
#		define panic dt_panic
#	endif
#elif defined(WINDOWS)
#	include "winduhz.h"
#else
#	error "Define an OS"
#endif
