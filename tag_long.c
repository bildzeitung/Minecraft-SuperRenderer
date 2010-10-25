// tag_long.c
//
// Created: 19 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "common.h"

int get_tag_long( gzFile f, TAG_LONG_TYPE *t) {
	int rc = gzread( f, t, 8 ) ;
	if ( rc != 8 ) {
		printf( "[TL] long read error\n" ) ;
		return FALSE;
	}

	// swap bytes; damn endianness
	*t = ((*t & 0xff)        << 56) | 
	     ((*t & 0xff00)      << 40) |
	     ((*t & 0xff0000)    << 24) |
		 ((*t & 0xff000000)  <<  8) |
		 ((*t >> 56) & 0xff       ) |
		 ((*t >> 40) & 0xff00     ) |
		 ((*t >> 24) & 0xff0000   ) |
		 ((*t >>  8) & 0xff000000 ) ;  
	
	//printf( "size: %i\n", sizeof(TAG_LONG_TYPE));
	//printf("[TL] %lld\n",*t);
	
	return TRUE;
}
