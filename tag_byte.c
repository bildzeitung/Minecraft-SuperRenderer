// tag_byte.c
//
// Created: 20 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include "common.h"

int get_tag_byte( gzFile f, char *s) {
	int rc = gzread( f, &s, 1 ) ;
	if ( rc != 1 ) {
		printf( "[TB] byte read error\n" ) ;
		return FALSE;
	}

	//printf("[TB] %i\n", s);
	
	return TRUE;
}
