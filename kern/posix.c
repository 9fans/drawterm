/*
 * Posix generic OS implementation for drawterm.
 */

#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <pwd.h>
#include <errno.h>

#include "u.h"
#include "lib.h"
#include "dat.h"
#include "fns.h"

typedef struct Oproc Oproc;
struct Oproc
{
	int p[2];
};

static pthread_key_t prdakey;

Proc*
_getproc(void)
{
	void *v;

	if((v = pthread_getspecific(prdakey)) == nil)
		panic("cannot getspecific");
	return v;
}

void
_setproc(Proc *p)
{
	if(pthread_setspecific(prdakey, p) != 0)
		panic("cannot setspecific");
}

void
osinit(void)
{
	if(pthread_key_create(&prdakey, 0))
		panic("cannot pthread_key_create");
}

#undef pipe
void
osnewproc(Proc *p)
{
	Oproc *op;

	op = (Oproc*)p->oproc;
	if(pipe(op->p) < 0)
		panic("cannot pipe");
}

void
osmsleep(int ms)
{
	struct timeval tv;

	tv.tv_sec = ms / 1000;
	tv.tv_usec = (ms % 1000) * 1000; /* micro */
	if(select(0, NULL, NULL, NULL, &tv) < 0)
		panic("select");
}

void
osyield(void)
{
	sched_yield();
}

void
oserrstr(void)
{
	char *p;
	char buf[ERRMAX];

	if((p = strerror(errno)) != nil)
		strecpy(up->errstr, up->errstr+ERRMAX, p);
	else
		snprint(up->errstr, ERRMAX, "unix error %d", errno);
}

void
oserror(void)
{
	oserrstr();
	nexterror();
}

static void* tramp(void*);

void
osproc(Proc *p)
{
	pthread_t pid;

	if(pthread_create(&pid, nil, tramp, p)){
		oserrstr();
		panic("osproc: %r");
	}
	sched_yield();
}

static void*
tramp(void *vp)
{
	Proc *p;

	p = vp;
	if(pthread_setspecific(prdakey, p))
		panic("cannot setspecific");
	(*p->fn)(p->arg);
	/* BUG: leaks Proc */
	pthread_setspecific(prdakey, 0);
	pthread_exit(0);
}

void
procsleep(void)
{
	int c;
	Proc *p;
	Oproc *op;

	p = up;
	op = (Oproc*)p->oproc;
	while(read(op->p[0], &c, 1) != 1)
		;
}

void
procwakeup(Proc *p)
{
	char c;
	Oproc *op;

	op = (Oproc*)p->oproc;
	c = 'a';
	write(op->p[1], &c, 1);
}

int randfd;
#undef open
void
randominit(void)
{
	if((randfd = open("/dev/urandom", OREAD)) < 0)
	if((randfd = open("/dev/random", OREAD)) < 0)
		panic("open /dev/random: %r");
}

#undef read
ulong
randomread(void *v, ulong n)
{
	int m;

	if((m = read(randfd, v, n)) != n)
		panic("short read from /dev/random: %d but %d", n, m);
	return m;
}

#undef time
long
seconds(void)
{
	return time(0);
}

ulong
ticks(void)
{
	static long sec0 = 0, usec0;
	struct timeval t;

	if(gettimeofday(&t, nil) < 0)
		return 0;
	if(sec0 == 0){
		sec0 = t.tv_sec;
		usec0 = t.tv_usec;
	}
	return (t.tv_sec-sec0)*1000+(t.tv_usec-usec0+500)/1000;
}

