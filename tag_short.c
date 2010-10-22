// tag_short.c
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "common.h"

int get_tag_short( gzFile f, short *s) {
	short t;
	
	int rc = gzread( f, &t, 2 ) ;
	if ( rc != 2 ) {
		printf( "[TS] short read error\n" ) ;
		return FALSE;
	}
	
	// swap bytes; damn endianness
	*s = ( (t & 0xff) << 8 ) | ((t >> 8) & 0xff) ;
	
	//printf("[TS] sizeof: %li\n", sizeof(short)) ;
	//printf("[TS] %i\n",*s);
	
	return TRUE;
}
