// named_tag.c
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "tag_string.h"
#include "named_tag.h"


int get_tag_type( gzFile f, int* tag ) {
	int t = 0;
	
	int rc = gzread( f, &t, 1);
	if ( rc != 1 ) {
		printf( "GZip read error\n" ) ;
		return FALSE ;
	}

	//printf( "[TT] %i\n", t ) ;

	*tag = t ;
	
	return TRUE ;	
}


int get_named_tag( gzFile f, Named_Tag *n ) {
	int type;
	char* name = NULL;
	
	int rv = get_tag_type( f, &type ) ;
	if ( rv != TRUE ) { printf( "[NT] error: short\n" ) ; return FALSE ; }

  if ( type != TAG_End ) {
	  rv = get_tag_string( f, &name ) ;
	  if ( rv != TRUE ) { printf( "[NT] error: string\n" ) ; return FALSE ; }
  }

	n->type = type ; n->name = name ;
	
	return TRUE;
}


void NT_dispose( Named_Tag *n ) {
	free( n->name ) ;
}