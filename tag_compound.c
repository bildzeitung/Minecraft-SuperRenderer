// tag_compound.c
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "named_tag.h"
#include "tag_compound.h"


int read_tag_compound( gzFile f, list* l ) {
	int rc;
	list* current = l;
	
	Named_Tag *n;
    n = (Named_Tag*)malloc(sizeof(Named_Tag));
	rc = read_named_tag( f, n );
	
	if ( !rc ) { printf( "[TC] cannot read first tag" ); return FALSE ;}
	while ( n->type != TAG_End ) {
		l_append( current, n );
		current = l->next;
	  
		n = (Named_Tag*)malloc(sizeof(Named_Tag));
		rc = read_named_tag( f, n );
		if ( !rc ) { printf( "[TC] cannot read tag in list" ); return FALSE ;}
	}

	return TRUE;
}
