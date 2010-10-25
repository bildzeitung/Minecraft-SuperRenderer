// main.c
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

#include "common.h"
#include "named_tag.h"

char* tag_labels[] = {
	"TAG_End",         // 0
	"TAG_Byte",        // 1
	"TAG_Short",       // 2
	"TAG_Int",         // 3
	"TAG_Long",        // 4
	"TAG_Float",       // 5
	"TAG_Double",      // 6
	"TAG_Byte_Array",  // 7
	"TAG_String",      // 8
	"TAG_List",        // 9
	"TAG_Compound"     // 10
};

int main( int argc, char** argv ) {
	gzFile f = gzopen( "test/bigtest.nbt", "r" ) ;
	//gzFile f = gzopen( "test/test.nbt", "r" ) ;
	if ( !f ) { printf( "Bad filename\n" ) ; return EXIT_FAILURE ;}

	Named_Tag tag;	
	int rv = read_named_tag( f, &tag ) ;	
	if ( !rv ) { printf( "[main] Could not get tag\n" ) ; return EXIT_FAILURE ;}
	
	// we expect the file to start with a compound tag
	if ( tag.type != TAG_Compound ) {
		printf( "Expected compound tag\n" ) ;
		return EXIT_FAILURE;
	}
	
	print_named_tag( &tag ) ;
	
	return EXIT_SUCCESS;
}
