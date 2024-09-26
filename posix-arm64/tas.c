#include "u.h"
#include "libc.h"

int
tas(int *x)
{
	int     v,t, i = 1;

	__asm__ (
		"1:	ldxr	%0, [%2]\n"
		"	stxr	%w1, %3, [%2]\n"
		"	cmp	%1, #0\n"
		"	bne	1b"
		: "=&r" (v), "=&r" (t)
		: "r" (x), "r" (i)
		: "cc");

	switch(v) {
	case 0:
	case 1:
		return v;
	default:
		print("canlock: corrupted 0x%lux\n", v);
		return 1;
	}
}

