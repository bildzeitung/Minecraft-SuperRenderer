// tag_compound.h
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>
#include "list.h"
#include "named_tag.h"


#ifndef __tag_compound_h
#define __tag_compound_h

typedef struct _TCompound {
	int count;
	list* payload;
	Named_Tag* tag;	
} TCompound;

TCompound* new_compound(Named_Tag*) ;
int read_TAG_Compound( gzFile, TCompound* ) ;

#endif