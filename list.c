// list.c
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#include <stdlib.h>
#include "list.h"

list* new_list() {
	list* l = (list*)malloc(sizeof(list));
	
	l->next  = NULL;
	l->data  = NULL;
	l->count = 0;
	
	return l;
}

void l_append( list* l, Named_Tag* i ) {
	l->data        = i;
	l->next        = new_list() ;	
	l->next->count = l->count ;
	l->count      += 1 ;
}
