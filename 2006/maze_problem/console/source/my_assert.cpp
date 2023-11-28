#include <stdio.h>
#include <stdlib.h>
#include "my_assert.h"

void _mAssert(char *f, unsigned l) {
	fflush(stdout);
	fprintf(stderr, "\nAssertion failed : %s, line %u\n", f, l);
	fflush(stderr);
	exit(0);
}