// list.h
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#ifndef __LIST__
#define __LIST__

typedef struct _list {
	void* data ;
	struct _list* next ;
	int count ;
} list ;

list* new_list() ;

void add_item( list*, void* ) ;

#endif