// main.c
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

#include "list.h"

#define TAG_End         0
#define TAG_Byte        1
#define TAG_Short       2
#define TAG_Int         3
#define TAG_Long        4
#define TAG_Float       5
#define TAG_Double      6
#define TAG_Byte_Array  7
#define TAG_String      8
#define TAG_TAG_List    9
#define TAG_Compound   10

#define TRUE  1
#define FALSE 0

typedef struct _Named_Tag {
	int type;
	char* name;
} Named_Tag;


int get_tag_type( gzFile f, int* tag ) {
	int t;
	
	int rc = gzread( f, &t, 1);
	if ( rc != 1 ) {
		printf( "GZip read error\n" ) ;
		return FALSE ;
	}

	//printf( "[TT] %i\n", t ) ;

	*tag = t ;
	
	return TRUE ;	
}

int get_tag_short( gzFile f, short *s) {
	short t;
	
	int rc = gzread( f, &t, 2 ) ;
	if ( rc != 2 ) {
		printf( "GZip short read error\n" ) ;
		return FALSE;
	}
	
	// swap bytes; damn endianness
	*s = ( (t & 8) << 8 ) | (t >> 8) ;
	
	return TRUE;
}

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

int read_TAG_Compound( gzFile f, list* l ) {
	printf( "[TAG Compound] {\n" ) ;
	
	Named_Tag n;
	int rv = get_named_tag( f, &n ) ;
	if ( rv != TRUE ) { printf( "[TC] cannot get member tag") ; return FALSE ; }
	
	while ( n.type != TAG_End ) {
		char *c;
		
		switch (n.type) {
			case TAG_String:
				rv = get_tag_string(f, &c);
				if ( rv != TRUE ) { 
					printf("[TC] error processing tag string\n") ; 
					return FALSE ;
				}
				
				add_item(l,c) ;
				
				break;
			default:
				printf( "[TC] Unknown tag type\n") ;
				return FALSE;
		}		

		NT_dispose( &n ) ;
		int rv = get_named_tag( f, &n ) ;
		if ( rv != TRUE ) { printf( "[TC] cannot get member tag") ; return FALSE ; }
	}
	
	printf( "[TC] compound tag has %i item(s)\n", l->count ) ;
	printf( "}\n") ;
	
	return TRUE;
}

int main( int argc, char** argv ) {
	gzFile f = gzopen( "test.nbt", "r" ) ;
	if ( !f ) { printf( "Bad filename\n" ) ; return EXIT_FAILURE ;}

	Named_Tag tag;
	int rv = get_named_tag( f, &tag ) ;	
	if ( rv != TRUE ) { printf( "Could not get tag type\n" ) ; return EXIT_FAILURE ;}
	
	// we expect the file to start with a compound tag
	if ( tag.type != TAG_Compound ) {
		printf( "Expect compound tag\n" ) ;
	}
	
	NT_dispose( &tag ) ;
	
	list* l = new_list();
	rv = read_TAG_Compound(f, l) ;
	if (rv != TRUE ) { 
		printf( "Compound tag read error\n") ; 
		return EXIT_FAILURE ; 
	}
	
	return EXIT_SUCCESS;
}
