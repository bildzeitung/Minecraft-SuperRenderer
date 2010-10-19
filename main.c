// main.c
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

#include "common.h"
#include "list.h"
#include "named_tag.h"
#include "tag_compound.h"


int main( int argc, char** argv ) {
	gzFile f = gzopen( "test/test.nbt", "r" ) ;
	if ( !f ) { printf( "Bad filename\n" ) ; return EXIT_FAILURE ;}

	Named_Tag tag;
	int rv = get_named_tag( f, &tag ) ;	
	if ( rv != TRUE ) { printf( "Could not get tag type\n" ) ; return EXIT_FAILURE ;}
	
	// we expect the file to start with a compound tag
	if ( tag.type != TAG_Compound ) {
		printf( "Expect compound tag\n" ) ;
	}
	
	NT_dispose( &tag ) ;
	
	TCompound *c = new_compound(&tag) ;
	rv = read_TAG_Compound(f, c) ;
	if (rv != TRUE ) { 
		printf( "Compound tag read error\n") ; 
		return EXIT_FAILURE ; 
	}
	
	return EXIT_SUCCESS;
}
