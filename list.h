// list.h
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//
#include "named_tag.h"

#ifndef __LIST__
#define __LIST__

typedef struct _list {
	Named_Tag* data ;
	struct _list* next ;
	int count ;
} list ;

list* new_list() ;

void l_append( list*, Named_Tag* ) ;

//Named_Tag* at( list*, int ) ;

#endif
