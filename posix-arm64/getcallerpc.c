#include "u.h"
#include "libc.h"

uintptr
getcallerpc(void *a)
{
	USED(a);
	return (uintptr)__builtin_extract_return_addr(__builtin_return_address(0));
}
