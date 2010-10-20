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
	  int   t;
	  float f;
	} bar;

	int rc = gzread( f, &(bar.t), 4 ) ;
	if ( rc != 4 ) {
		printf( "[TF] float read error\n" ) ;
		return FALSE;
	}
	
	bar.t = ((bar.t & 0xff) << 24) | ((bar.t & 0xff00) << 8) |
             ((bar.t >> 8) & 0xff00) | ((bar.t >> 24)&0xff);
	
	*s = bar.f;
	
	//printf("[TF] %f\n", *s);
	
	return TRUE;
}
