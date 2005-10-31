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

static int tlsx = TLS_OUT_OF_INDEXES;

char	*argv0;

Proc*
_getproc(void)
{
	if(tlsx == TLS_OUT_OF_INDEXES)
		return nil;
	return TlsGetValue(tlsx);
}

void
_setproc(Proc *p)
{
	if(tlsx == TLS_OUT_OF_INDEXES){
		tlsx = TlsAlloc();
		if(tlsx == TLS_OUT_OF_INDEXES)
			panic("out of indexes");
	}
	TlsSetValue(tlsx, p);
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

	_setproc(&firstprocCTstore);
	t = (Oproc*)firstprocCTstore.oproc;
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
	DWORD tid;

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

	_setproc(p);
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

#if 0
uvlong
fastticks(uvlong *v)
{
	uvlong n;

	n = GetTickCount() * 1000 * 1000;
	if(v)
		*v = n;
	return n;
}
#endif

extern int	main(int, char*[]);
static int	args(char *argv[], int n, char *p);

int APIENTRY
WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR arg, int nshow)
{
	main(__argc, __argv);
	ExitThread(0);
	return 0;
}

/*
 * Windows socket error messages
 * There must be a way to get these strings out of the library.
 * This table is derived from the MSDN online help.
 */
static struct {
	int e;
	char *s;
} tab[] = {
	{ 10004, "interrupted function call" },
	{ 10013, "permission denied" },
	{ 10014, "bad address" },
	{ 10022, "invalid argument" },
	{ 10024, "too many open files" },
	{ 10035, "resource temporarily unavailable" },
	{ 10036, "operation now in progress" },
	{ 10037, "operation already in progress" },
	{ 10038, "socket operation on nonsocket" },
	{ 10039, "destination address required" },
	{ 10040, "message too long" },
	{ 10041, "protocol wrong type for socket" },
	{ 10042, "bad protocol option" },
	{ 10043, "protocol not supported" },
	{ 10044, "socket type not supported" },
	{ 10045, "operation not supported" },
	{ 10046, "protocol family not supported" },
	{ 10047, "address family not supported by protocol family" },
	{ 10048, "address already in use" },
	{ 10049, "cannot assign requested address" },
	{ 10050, "network is down" },
	{ 10051, "network is unreachable" },
	{ 10052, "network dropped connection on reset" },
	{ 10053, "software caused connection abort" },
	{ 10054, "connection reset by peer" },
	{ 10055, "no buffer space available" },
	{ 10056, "socket is already connected" },
	{ 10057, "socket is not connected" },
	{ 10058, "cannot send after socket shutdown" },
	{ 10060, "connection timed out" },
	{ 10061, "connection refused" },
	{ 10064, "host is down" },
	{ 10065, "no route to host" },
	{ 10067, "too many processes" },
	{ 10091, "network subsystem is unavailable" },
	{ 10092, "winsock.dll version out of range" },
	{ 10093, "wsastartup not called" },
	{ 10101, "graceful shutdown in progress" },
	{ 10109, "class type not found" },
	{ 11001, "host name not found" },
	{ 11002, "host not found (non-authoritative)" },
	{ 11003, "nonrecoverable error" },
	{ 11004, "valid name, but no data record of requested type" },
};

void
osrerrstr(char *buf, uint nbuf)
{
	char *p, *q;
	int e, i, r;

	e = GetLastError();
	r = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
		0, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		buf, nbuf, 0);
	if(r == 0){
		for(i=0; i<nelem(tab); i++)
			if(tab[i].e == e){
				strecpy(buf, buf+nbuf, tab[i].s);
				break;
			}
		if(i==nelem(tab))
			snprint(buf, nbuf, "windows error %d", e);
	}

	for(p=q=buf; *p; p++) {
		if(*p == '\r')
			continue;
		if(*p == '\n')
			*q++ = ' ';
		else
			*q++ = *p;
	}
	*q = '\0';
}

void
oserrstr(void)
{
	osrerrstr(up->errstr, ERRMAX);
}
