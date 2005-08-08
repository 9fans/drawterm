#include "u.h"
#include "lib.h"
#include "dat.h"
#include "fns.h"
#include "error.h"

extern Dev consdevtab;
extern Dev rootdevtab;
extern Dev pipedevtab;
extern Dev ssldevtab;
extern Dev mousedevtab;
extern Dev drawdevtab;
extern Dev ipdevtab;
extern Dev fsdevtab;

Dev *devtab[] = {
	&rootdevtab,
	&consdevtab,
	&pipedevtab,
	&ssldevtab,
	&mousedevtab,
	&drawdevtab,
	&ipdevtab,
	&fsdevtab,
	0
};

