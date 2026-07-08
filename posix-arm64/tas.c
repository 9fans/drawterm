#include "u.h"
#include "libc.h"

int
tas(int *x)
{
	return __atomic_test_and_set(x, __ATOMIC_ACQ_REL);
}
