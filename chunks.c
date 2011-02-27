// chunks.c
//
// Created: 19 FEB 2011
// Author : Daniel M. Klein
//

#include "chunks.h"

chunk_t* chunks = NULL ;


void add_chunk( int x, int z, unsigned char* d ) {
  // prep
  chunk_t* c = malloc(sizeof(chunk_t));
  memset(c,0,sizeof(chunk_t));

  // configure
  memcpy(c->data,d,BLOCKSIZE);
  c->xPos = x ; c->zPos = z;

  int key_len = offsetof(chunk_t,zPos)
                + sizeof(int) - offsetof(chunk_t,xPos);
	
  // add
  HASH_ADD( hh, chunks, xPos, key_len, c);
}

/*
int chunk_sort(chunk_t* a, chunk_t* b) {
	return (
		(a->xPos > b->xPos) ? 1 : 
		(a->zPos > b->zPos) ? 1 : -1
	);
}
*/

void scan_chunks() {
	//HASH_SORT( chunks, chunk_sort ) ;
	chunk_t* c;
	for ( c = chunks ; c != NULL ; c=c->hh.next) {
		printf( "(%i,%i)\n", c->xPos, c->zPos ) ;
	}
}
