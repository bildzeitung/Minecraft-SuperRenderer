// tag_byte_array.c
//
// Created: 20 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "tag_int.h"
#include "tag_byte_array.h"

int get_tag_byte_array( gzFile f, byte_array* s) {
	int rc;

	rc = get_tag_int( f, &(s->length) );
	if ( !rc ) {
		printf( "[TBA] cannot get byte array length\n" ) ;
		return FALSE;
	}

	//printf( "[TBA] length: %i\n", length ) ;
	
	void* barray = malloc(s->length);
	
	rc = gzread( f, barray, s->length ) ;
	if ( rc != s->length ) {
		printf( "[TBA] cannot read %i bytes\n", s->	length ) ;
		return FALSE;
	}

	s->data = barray;
	
	return TRUE;
}
