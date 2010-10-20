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

int get_tag_byte_array( gzFile f, void **s) {
	int rc;

	int length; 
	rc = get_tag_int( f, &length );
	if ( !rc ) {
		printf( "[TBA] cannot get byte array length\n" ) ;
		return FALSE;
	}

	//printf( "[TBA] length: %i\n", length ) ;
	
	void* barray = malloc(length);
	
	rc = gzread( f, barray, length ) ;
	if ( rc != length ) {
		printf( "[TBA] cannot read %i bytes\n", length ) ;
		return FALSE;
	}

	*s = barray;
	
	return TRUE;
}
