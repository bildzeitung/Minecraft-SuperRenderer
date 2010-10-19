// tag_compound.c
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "tag_string.h"
#include "tag_compound.h"


TCompound* new_compound(Named_Tag *t) {
	TCompound* c = (TCompound*)malloc(sizeof(TCompound)) ;

	c->tag     = t;
	c->count   = 0;
	c->payload = new_list();
	
	return c;	
}


int read_TAG_Compound( gzFile f, TCompound* l ) {
	printf( "TAG_Compound(\"%s\"): ", l->tag->name ) ;
	
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
				
				add_item(l->payload,c) ;
				l->count++ ;
				
				break;
			default:
				printf( "[TC] Unknown tag type\n") ;
				return FALSE;
		}		

		NT_dispose( &n ) ;
		int rv = get_named_tag( f, &n ) ;
		if ( rv != TRUE ) { printf( "[TC] cannot get member tag") ; return FALSE ; }
	}

	printf( "%i entries\n", l->count ) ;
	printf( "{\n" ) ;
	printf( "}\n" ) ;	
	
	return TRUE;
}