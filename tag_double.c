// tag_double.c
//
// Created: 21 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "common.h"

int get_tag_double( gzFile f, double *s) {
    union foo {
	  long   t;
	  double f;
	} bar;

	int rc = gzread( f, &(bar.t), 8 ) ;
	if ( rc != 8 ) {
		printf( "[TD] double read error\n" ) ;
		return FALSE;
	}
		
	bar.t = ((bar.t & 0xff)        << 56) | 
	        ((bar.t & 0xff00)      << 40) |
			    ((bar.t & 0xff0000)    << 24) |
			    ((bar.t & 0xff000000) 	 <<  8) |
			    ((bar.t >> 56) & 0xff       ) |
			    ((bar.t >> 40) & 0xff00     ) |
			    ((bar.t >> 24) & 0xff0000   ) |
					((bar.t >>  8) & 0xff000000 ) ;  
	
	*s = bar.f;
	
	//printf("[TD] %.16F\n", *s);
	
	return TRUE;
}
