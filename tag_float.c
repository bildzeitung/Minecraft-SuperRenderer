// tag_float.c
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "common.h"

int get_tag_float( gzFile f, float *s) {
    union foo {
	  char  t[4];
	  float f;
	} bar;

	char t[4] ;
	int rc = gzread( f, t, 4 ) ;
	if ( rc != 4 ) {
		printf( "[TF] float read error\n" ) ;
		return FALSE;
	}
		
    bar.t[0] = t[3];
    bar.t[1] = t[2];
    bar.t[2] = t[1];
    bar.t[3] = t[0];

	*s = bar.f;
	
	//printf("[TF] %f\n", *s);
	
	return TRUE;
}
