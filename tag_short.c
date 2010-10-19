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
		printf( "GZip short read error\n" ) ;
		return FALSE;
	}
	
	// swap bytes; damn endianness
	*s = ( (t & 8) << 8 ) | (t >> 8) ;
	
	//printf("[TS] %i\n",*s);
	
	return TRUE;
}
