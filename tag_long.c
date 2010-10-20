// tag_long.c
//
// Created: 19 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "common.h"

int get_tag_long( gzFile f, long long *s) {
	long long t = 0;
	
	int rc = gzread( f, &t, 8 ) ;
	if ( rc != 8 ) {
		printf( "[TL] long read error\n" ) ;
		return FALSE;
	}
	
	// swap bytes; damn endianness
	*s = t ; //( (t & 16) << 16 ) | (t >> 16) ;
	
	//printf("[TL] %i\n",*s);
	
	return TRUE;
}
