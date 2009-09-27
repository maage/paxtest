/* shlibbss.c - Tests whether code in the .bss segment of a shared library can
 *              be executed
 *
 * Copyright (c)2003 by Peter Busser <peter@adamantix.org>
 * This file has been released under the GNU Public Licence version 2 or later
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "body.h"

const char testname[] = "Executable shared library bss            ";

static char *shbss, *shbss2;

void doit( void )
{
	fptr func;
	void *handle1, *handle2;

	handle1 = dlopen( "shlibtest.so", RTLD_LAZY );
	if( handle1 == NULL ) {
		fprintf( stderr, "dlopen() returned NULL\n" );
		exit( 1 );
	}
	dlerror(); /* clear any errors */
	shbss = dlsym( handle1, "shbss" );
	if( dlerror() != NULL ) {
		fprintf( stderr, "symbol %s not found in %s\n", "shbss", "shlibtest.so" );
		exit( 1 );
	}

	handle2 = dlopen( "shlibtest2.so", RTLD_LAZY );
	if( handle2 == NULL ) {
		fprintf( stderr, "dlopen() returned NULL\n" );
		exit( 1 );
	}
	dlerror(); /* clear any errors */
	shbss2 = dlsym( handle2, "shbss2" );
	if( dlerror() != NULL ) {
		fprintf( stderr, "symbol %s not found in %s\n", "shbss2", "shlibtest2.so" );
		exit( 1 );
	}

	/* Put a RETN instruction in the buffer */
	*shbss = '\xc3';
	*shbss2 = '\xc3';

	/* Convert the pointer to a function pointer */
	func = shbss < shbss2 ? (fptr)shbss : (fptr)shbss2;

	/* Call the code in the buffer */
	func();

	/* It worked when the function returns */
	itworked();

	dlclose( handle1 );
	dlclose( handle2 );
}
