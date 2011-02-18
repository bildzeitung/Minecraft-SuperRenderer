// callbacks.h
//
// Created: 13 FEB 2011
// Author : Daniel M. Klein
//

#ifndef __callbacks_h__
#define __callbacks_h__

#include <stdlib.h>
#include <string.h>

#include <uthash.h>

#include "common.h"
#include "named_tag.h"

typedef int(*callback_fn)(const Named_Tag*);

typedef struct _callback_entry {
	callback_fn f;
	char *name;
	UT_hash_handle hh;
} callback_entry;

extern callback_entry *callback_table;

void register_named_tag( const char*, callback_fn ) ;
void unregister_named_tag( const char* ) ;
int  exec_named_tag_callbacks( const Named_Tag* ) ;

#endif