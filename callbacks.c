// callbacks.c
//
// Created: 13 FEB 2011
// Author : Daniel M. Klein
//

#include "callbacks.h"
#include <stdio.h>

callback_entry *callback_table = NULL ;


void register_named_tag( const char* n, callback_fn f ) {	
	callback_entry *c = malloc(sizeof(callback_entry));
	
	c->name = malloc(sizeof(char)*(strlen(n)+1));
	strcpy(c->name,n) ;
	
	c->f = f;

  HASH_ADD_KEYPTR( hh, callback_table, c->name, strlen(c->name), c );
}

void unregister_named_tag( const char* n ) {
	callback_entry *c;
	HASH_FIND_STR( callback_table, n, c ) ;
	HASH_DELETE(hh, callback_table, c) ;
}

int exec_named_tag_callbacks(const Named_Tag* n) {
	int rc = TRUE ;
	callback_entry *c;

	if ( n->name == NULL ) return rc;

  HASH_FIND_STR( callback_table, n->name, c );
	
	if (c) rc = c->f(n) ;
	
	return rc ;
}