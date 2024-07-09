#include <u.h>
#include <libc.h>
#include "fmtdef.h"

static int
runeFmtStrFlush(Fmt *f)
{
	Rune *s;
	int n, d;

	if(f->start == nil)
		return 0;
	n = (uintptr)f->farg;
	n *= 2;
	d = (Rune*)f->to - (Rune*)f->start;
	s = realloc(f->start, sizeof(Rune)*n);
	if(s == nil){
		f->farg = nil;
		f->to = nil;
		f->stop = nil;
		free(f->start);
		return 0;
	}
	f->start = s;
	f->farg = (void*)(uintptr)n;
	f->to = (Rune*)f->start + d;
	f->stop = (Rune*)f->start + n - 1;
	return 1;
}

int
runefmtstrinit(Fmt *f)
{
	int n;

	memset(f, 0, sizeof *f);
	f->runes = 1;
	n = 32;
	f->start = malloc(sizeof(Rune)*n);
	if(f->start == nil)
		return -1;
	f->to = f->start;
	f->stop = (Rune*)f->start + n - 1;
	f->flush = runeFmtStrFlush;
	f->farg = (void*)(uintptr)n;
	f->nfmt = 0;
	return 0;
}

/*
 * print into an allocated string buffer
 */
Rune*
runevsmprint(char *fmt, va_list args)
{
	Fmt f;
	int n;

	if(runefmtstrinit(&f) < 0)
		return nil;
	VA_COPY(f.args,args);
	n = dofmt(&f, fmt);
	VA_END(f.args);
	if(f.start == nil)
		return nil;
	if(n < 0){
		free(f.start);
		return nil;
	}
	*(Rune*)f.to = '\0';
	return (Rune*)f.start;
}
