// list.c
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#include <stdlib.h>
#include "list.h"

list* new_list() {
	list* l = (list*)malloc(sizeof(list));
	
	l->next = NULL;
	l->count = 0;
	l->data = NULL;
	
	return l;
}

void add_item( list* l, void* i ) {
	list* n = (list*)malloc(sizeof(list)) ;
	
	n->next = NULL;
	n->data = i;
	n->count = l->count;
	
	l->count += 1 ;
	l->next = n ;	
}