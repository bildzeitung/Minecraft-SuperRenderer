// tag_list.h
//
// Created: 20 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include "list.h"
#include "named_tag.h"


#ifndef __tag_list_h
#define __tag_list_h

typedef struct _rough_list {
	int    length;
	int    type;
	void** payload;
} rough_list;

int read_tag_list( gzFile, rough_list* ) ;

#endif
