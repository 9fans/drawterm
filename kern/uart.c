#include "u.h"
#include "lib.h"
#include "dat.h"
#include "fns.h"
#include "error.h"

#undef write
void
uartputs(char *s, int n)
{
	write(1, s, n); 
}


