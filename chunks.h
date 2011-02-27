// chunks.h
//
// Created: 19 FEB 2011
// Author : Daniel M. Klein
//

#ifndef __chunks_h__
#define __chunks_h__

#include <stdlib.h>    /* malloc       */
#include <stddef.h>    /* offsetof     */
#include <stdio.h>     /* printf       */
#include <string.h>    /* memset       */
#include <uthash.h>

#include "common.h"

#define BLOCKSIZE 32768

typedef struct _chunk_t {
	int xPos;
	int zPos;
	char data[BLOCKSIZE];
	UT_hash_handle hh;
} chunk_t;

typedef struct _chunk_lookup { 
	int xPos; 
	int zPos; 
} chunk_lookup ;

extern chunk_t* chunks;

void add_chunk( int, int, unsigned char* );
void scan_chunks();

#endif
