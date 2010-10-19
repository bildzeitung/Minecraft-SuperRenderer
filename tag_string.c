// tag_string.c
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include "common.h"
#include "tag_short.h"
#include "tag_string.h"

int get_tag_string( gzFile f, char** TString ) {
	int rv = TRUE;
	
	short len ;
	rv = get_tag_short(f, &len);
	if ( rv != TRUE ) { printf( "Bad string\n" ) ; return rv; }

	//printf( "[TS] len: %i\n", len ) ;
	
	char* s = (char*)malloc(sizeof(char)*(len+1)) ;
	s[len] = 0;
	
	int rc = gzread( f, s, len ) ;
  if ( rc != len ) {
		printf( "GZip read string error\n" ) ;
		return FALSE ;
	}
	
	//printf( "[TS] |%s|\n", s ) ;
	
	*TString = s;
	
	return rv;
}