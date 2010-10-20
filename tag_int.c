// tag_int.c
//
// Created: 20 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "common.h"

int get_tag_int( gzFile f, int *s) {
	int t;
	
	int rc = gzread( f, &t, 4 ) ;
	if ( rc != 4 ) {
		printf( "[TI] int read error\n" ) ;
		return FALSE;
	}
	
	// swap bytes; damn endianness
        *s = ((t & 0xff) << 24) | ((t & 0xff00) << 8) |
             ((t >> 8) & 0xff00) | ((t >> 24)&0xff);
	
	//printf("[TI] %i\n",*s);
	
	return TRUE;
}
