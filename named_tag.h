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
void NT_dispose( Named_Tag* ) ;


void print_named_tag( Named_Tag* ) ;
int read_named_tag( gzFile, Named_Tag* ) ;

#endif
