#include "u.h"
#include "libc.h"

int
tas(int *x)
{
	int v, i = 1;

	 __asm__(
		"1:    ll.w $r12, %1, 0\n"
		"      or $r13, %2, $zero\n"
		"      sc.w $r13, %1, 0\n"
		"      beqz $r13, 1b\n"
		"      move %0, $r12"
                : "=r" (v)
                : "r" (x), "r" (i)
                : "$r13", "$r12"
	 );

	switch(v) {
	case 0:
	case 1:
		return v;
	default:
		print("canlock: corrupted 0x%lux\n", v);
		return 1;
	}
}

