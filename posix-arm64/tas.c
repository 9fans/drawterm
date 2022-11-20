#include "u.h"
#include "libc.h"

int
tas(int *x)
{
	int	v,t;

	__asm__(
		"mov	%w1, #1\n"
		"swpalb	%w1, %w1, [%2]\n"
		"cmp	%w1, #0\n"
		"cset	%w0, ne"
		: "=&r" (v), "=&r" (t)
		: "r" (x)
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
