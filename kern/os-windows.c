#include <windows.h>
#include "u.h"
#include "lib.h"
#include "dat.h"
#include "fns.h"

typedef struct Oproc Oproc;
struct Oproc {
	int tid;
	HANDLE	*sema;
};

char	*argv0;
_declspec(thread)       Proc *CT;

Proc*
_getproc(void)
{
	return CT;
}

void
_setproc(Proc *p)
{
	CT = p;
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

void
osinit(void)
{
	Oproc *t;
	static Proc firstprocCTstore;

	CT = &firstprocCTstore;
	t = (Oproc*) CT->oproc;
	assert(t != 0);

	t->tid = GetCurrentThreadId();
	t->sema = CreateSemaphore(0, 0, 1000, 0);
	if(t->sema == 0) {
		oserror();
		fatal("could not create semaphore: %r");
	}
}

void
osnewproc(Proc *p)
{
	Oproc *op;

	op = (Oproc*)p->oproc;
	op->sema = CreateSemaphore(0, 0, 1000, 0);
	if (op->sema == 0) {
		oserror();
		fatal("could not create semaphore: %r");
	}
}

void
osmsleep(int ms)
{
	Sleep((DWORD) ms);
}

void
osyield(void)
{
	Sleep(0);
}

static DWORD WINAPI tramp(LPVOID vp);

void
osproc(Proc *p)
{
	int tid;

	if(CreateThread(0, 0, tramp, p, 0, &tid) == 0) {
		oserror();
		fatal("osproc: %r");
	}

	Sleep(0);
}

static DWORD WINAPI
tramp(LPVOID vp)
{
	Proc *p = (Proc *) vp;
	Oproc *op = (Oproc*) p->oproc;

	CT = p;
	op->tid = GetCurrentThreadId();
	op->sema = CreateSemaphore(0, 0, 1000, 0);
	if(op->sema == 0) {
		oserror();
		fatal("could not create semaphore: %r");
	}

 	(*p->fn)(p->arg);
	ExitThread(0);
	return 0;
}

void
procsleep(void)
{
	Proc *p;
	Oproc *op;

	p = up;
	op = (Oproc*)p->oproc;
	WaitForSingleObject(op->sema, INFINITE);}

void
procwakeup(Proc *p)
{
	Oproc *op;

	op = (Oproc*)p->oproc;
	ReleaseSemaphore(op->sema, 1, 0);
}

void
randominit(void)
{
	srand(seconds());
}

ulong
randomread(void *v, ulong n)
{
	int m, i, *r;

	m = (n / sizeof(int)) * sizeof(int);
	for (i = 0, r = (int*)v; i < m; i += sizeof(int)) {
		*r = rand();
		r += sizeof(int);
	}

	return m;
}

long
seconds(void)
{
	return time(0);
}

int
ticks(void)
{
	return GetTickCount();
}

extern int	main(int, char*[]);
static int	args(char *argv[], int n, char *p);

int PASCAL
WinMain(HANDLE hInst, HANDLE hPrev, LPSTR arg, int nshow)
{
	main(__argc, __argv);
	ExitThread(0);
	return 0;
}
