/*
 * 64-bit IEEE not-a-number routines.
 * This is big/little-endian portable assuming that 
 * the 64-bit doubles and 64-bit integers have the
 * same byte ordering.
 */

#include <u.h>
#include <libc.h>
#include "nan.h"

// typedef unsigned long long uvlong;
// typedef unsigned long ulong;

static uvlong uvnan    = 0x7FF0000000000001;
static uvlong uvinf    = 0x7FF0000000000000;
static uvlong uvneginf = 0xFFF0000000000000;

double
__NaN(void)
{
	return *(double*)&uvnan;
}

int
__isNaN(double d)
{
	uvlong x = *(uvlong*)&d;
	return (ulong)(x>>32)==0x7FF00000 && !__isInf(d, 0);
}

double
__Inf(int sign)
{
	if(sign < 0)
		return *(double*)&uvinf;
	else
		return *(double*)&uvneginf;
}

int
__isInf(double d, int sign)
{
	uvlong x;

	x = *(uvlong*)&d;
	if(sign == 0)
		return x==uvinf || x==uvneginf;
	else if(sign > 0)
		return x==uvinf;
	else
		return x==uvneginf;
}


