// could also use windozy InterlockedCompareExchange(p, 1, 0), but why
int
tas(long *p)
{	
	int v;
	
	_asm {
		mov	eax, p
		mov	ebx, 1
		xchg	ebx, [eax]
		mov	v, ebx
	}

	switch(v) {
	case 0:
	case 1:
		return v;
	default:
		print("canlock: corrupted 0x%lux\n", v);
		return 1;
	}
}
