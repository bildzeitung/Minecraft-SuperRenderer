// tag_double.c
//
// Created: 21 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "tag_long.h"
#include "common.h"

int get_tag_double( gzFile f, double *s) {
    union foo {
	  TAG_LONG_TYPE  t;
	  double         f;
	} bar;

	int rc = get_tag_long( f, &(bar.t) ) ;
	if ( !rc ) {
		printf( "[TD] double read error\n" );
		return FALSE;
	}
	
	*s = bar.f;

    //printf("[TD] sizeof: %i\n", sizeof(double));
	//printf("[TD] %.16F\n", *s);
	
	return TRUE;
}
