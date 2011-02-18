// tag_print.c
//
// Created: 25 OCT 2010
// Author : Daniel M. Klein
//

#include <stdio.h>
#include "tag_long.h"
#include "tag_byte_array.h"
#include "tag_list.h"
#include "tag_print.h"

print_tag_fn print_fns[] = {
	print_TAG_End,        //  0
	print_TAG_Byte,       //  1
	print_TAG_Short,      //  2
	print_TAG_Int,        //  3
	print_TAG_Long,       //  4
	print_TAG_Float,      //  5
	print_TAG_Double,     //  6
	print_TAG_Byte_Array, //  7
	print_TAG_String,     //  8
	print_TAG_List,       //  9
	print_TAG_Compound    // 10	 */
};

void _print_indent( int i ) {
	for (int j = 0 ; j < i ; j++ ) printf("  ") ;
}

void print_TAG_End( const Named_Tag* n, int i ) {}

void print_TAG_Byte( const Named_Tag* n, int i ) {
	printf( "%u\n", ((unsigned char*)n->payload)[0] ) ;
}

void print_TAG_Short( const Named_Tag* n, int i ) {
  printf( "%i\n", *((short*)n->payload));	
}

void print_TAG_Int( const Named_Tag* n, int i ) {
	printf( "%i\n", *((int*)n->payload));	
}

void print_TAG_Long( const Named_Tag* n, int i ) {
#ifdef TAG_LONG_LONG
  printf( "%lld\n", *((TAG_LONG_TYPE*)n->payload));
#else
  printf( "%li\n", *((TAG_LONG_TYPE*)n->payload));
#endif
}

void print_TAG_Float( const Named_Tag* n, int i ) {
	printf( "%.8f\n", *((float*)n->payload));
}

void print_TAG_Double( const Named_Tag* n, int i ) {
  printf( "%.16f\n", *((double*)n->payload));
}

void print_TAG_Byte_Array( const Named_Tag* n, int i ) {
	byte_array* b = (byte_array*)n->payload;
	
	printf( "[%i bytes]\n", b->length) ;
	
	_print_indent( i+1 ) ;
	printf( "%u", b->data[0] ) ;
	int printlen = (b->length > 10) ? 10 : b->length;
	for ( i = 1 ; i < printlen ; i++ ) {
		printf( ", %u", b->data[i] ) ;
	}
	printf("\n");
}

void print_TAG_String( const Named_Tag* n, int i ) {
	printf( "%s\n", (char*)n->payload );
}

void print_TAG_List( const Named_Tag* n, int i ) {
	rough_list* r = (rough_list*)n->payload;
	
	printf("%i entries of type %s\n", r->length, tag_labels[r->type] ) ;
	_print_indent( i ) ; printf( "{\n" ) ;
	
	for (int j = 0; j < r->length ; j++ ) {
		Named_Tag q;
		q.type    = r->type;
		q.payload = r->payload[j];
	
		_print_indent(i+1);
		printf( "%s: ", tag_labels[r->type] ) ;
		print_fns[r->type](&q, i+1) ;
	}
	
	_print_indent( i ) ; printf( "}\n" ) ;	
}

void print_TAG_Compound( const Named_Tag* n, int i ) {
	list* l = (list*)n->payload;
	
	printf( "%i entries\n", l->count) ;
	_print_indent( i ) ; printf( "{\n" ) ;
	
  while ( l->next != NULL ) {
	  _print_named_tag( l->data, i+1 ) ;
	  l = l->next ;
  }
	
	_print_indent( i ) ; printf( "}\n" ) ;
}

void _print_named_tag( const Named_Tag* n, int indent_in ) {	
	_print_indent(indent_in);
	printf( "%s(\"%s\"): ", tag_labels[n->type], n->name ) ;
	print_fns[n->type](n, indent_in) ;
}
