/* mprotshdata.c - Tests wether code in the .data segment of a shared library
 *                 can be executed after trying to use mprotect() to make it
 *                 executable.
 *
 * Copyright (c)2003 by Peter Busser <peter@trusteddebian.org>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "body.h"

char *testname = "Executable shared library data (mprotect)";

extern char bufdata;

void doit( void )
{
	void (*func)(void);

	/* Try to make the memory region executable by using mprotect() */
	do_mprotect( &bufdata, 1, PROT_EXEC );

	/* Convert the pointer to a function pointer */
	func = (void (*)(void))&bufdata;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();
}

