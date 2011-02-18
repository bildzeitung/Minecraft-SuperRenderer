// named_tag.h
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>

#ifndef __named_tag_h
#define __named_tag_h

typedef struct _Named_Tag {
	int type;
	char* name;
	void* payload;
} Named_Tag;

int get_tag_type( gzFile, int* ) ;
int get_named_tag( gzFile, Named_Tag* ) ;

// memory handling
Named_Tag* NT_new() ;
void NT_dispose( Named_Tag* ) ;


void print_named_tag( const Named_Tag* ) ;
int read_named_tag( gzFile, Named_Tag* ) ;

#endif
