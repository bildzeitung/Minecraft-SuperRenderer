// named_tag.c
//
// Created: 18 OCT 2010
// Author : Daniel M. Klein
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "common.h"
#include "list.h"
#include "tag_byte.h"
#include "tag_short.h"
#include "tag_int.h"
#include "tag_long.h"
#include "tag_float.h"
#include "tag_double.h"
#include "tag_byte_array.h"
#include "tag_string.h"
#include "tag_list.h"
#include "tag_compound.h"
#include "named_tag.h"

typedef void(*print_tag_fn)(Named_Tag*, int) ;

void print_TAG_End(Named_Tag*, int) ;
void print_TAG_Byte(Named_Tag*, int) ;
void print_TAG_Short(Named_Tag*, int) ;
void print_TAG_Int(Named_Tag*, int) ;
void print_TAG_Long(Named_Tag*, int) ;
void print_TAG_Float(Named_Tag*, int) ;
void print_TAG_Double(Named_Tag*, int) ;
void print_TAG_Byte_Array(Named_Tag*, int) ;
void print_TAG_String(Named_Tag*, int) ;
void print_TAG_List(Named_Tag*, int) ;
void print_TAG_Compound(Named_Tag*, int) ;


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

void _print_named_tag( Named_Tag*, int ) ;

void _print_indent( int i ) {
	for (int j = 0 ; j < i ; j++ ) printf("  ") ;
}

void _print_tag_head( Named_Tag* n, int indent_in ) {
	_print_indent(indent_in);
	printf( "%s(\"%s\"): ", tag_labels[n->type], n->name ) ;
}

void print_TAG_End( Named_Tag* n, int i ) {}

void print_TAG_Byte( Named_Tag* n, int i ) {
	printf( "%u\n", ((unsigned char*)n->payload)[0] ) ;
}

void print_TAG_Short( Named_Tag* n, int i ) {
  printf( "%i\n", *((short*)n->payload));	
}

void print_TAG_Int( Named_Tag* n, int i ) {
	printf( "%i\n", *((int*)n->payload));	
}

void print_TAG_Long( Named_Tag* n, int i ) {
#ifdef TAG_LONG_LONG
  printf( "%lld\n", *((TAG_LONG_TYPE*)n->payload));
#else
  printf( "%li\n", *((TAG_LONG_TYPE*)n->payload));
#endif
}

void print_TAG_Float( Named_Tag* n, int i ) {
	printf( "%.8f\n", *((float*)n->payload));
}

void print_TAG_Double( Named_Tag* n, int i ) {
  printf( "%.16f\n", *((double*)n->payload));
}

void print_TAG_Byte_Array( Named_Tag* n, int i ) {
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

void print_TAG_String( Named_Tag* n, int i ) {
	printf( "%s\n", (char*)n->payload );
}

void print_TAG_List( Named_Tag* n, int i ) {
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

void print_TAG_Compound( Named_Tag* n, int i ) {
	list* l = (list*)n->payload;
	
	printf( "%i entries\n", l->count) ;
	_print_indent( i ) ; printf( "{\n" ) ;
	
  while ( l->next != NULL ) {
	  _print_named_tag( l->data, i+1 ) ;
	  l = l->next ;
  }
	
	_print_indent( i ) ; printf( "}\n" ) ;
}





void _print_named_tag( Named_Tag* n, int indent_in ) {	
	_print_tag_head(n, indent_in) ;
	print_fns[n->type](n, indent_in) ;
}

void print_named_tag( Named_Tag* n ) {
  _print_named_tag( n, 0 ) ;
}


int read_named_tag( gzFile f, Named_Tag* n ) {
  int rc;
  
  rc = get_named_tag(f, n ) ;
  if ( !rc ) { printf( "[NT] Could not read named tag\n" ) ; return FALSE ; }
  
  //printf("[NT] Handling tag %s\n", n->name ) ;
  
  switch ( n->type ) {
	case TAG_End:        //  0
	  n->payload = NULL;
	  break;
	case TAG_Byte:       //  1
	  n->payload = malloc(sizeof(unsigned char));
	  rc = get_tag_byte( f, n->payload ) ;
	  break;
	case TAG_Short:      //  2
	  n->payload = malloc(sizeof(short));
	  rc = get_tag_short( f, n->payload ) ;
	  break;
	case TAG_Int:        //  3
	  n->payload = malloc(sizeof(int));
	  rc = get_tag_int( f, n->payload ) ;
	  break;
	case TAG_Long:       //  4
	  n->payload = malloc(sizeof(long));
	  rc = get_tag_long( f, n->payload ) ;
	  break;
	case TAG_Float:      //  5
	  n->payload = malloc(sizeof(float));
	  rc = get_tag_float( f, n->payload ) ;
	  break;
	case TAG_Double:     //  6
		n->payload = malloc(sizeof(double));
		rc = get_tag_double( f, n->payload ) ;
		break;
	case TAG_Byte_Array: //  7
	  n->payload = malloc(sizeof(byte_array));
	  rc = get_tag_byte_array( f, n->payload );
	  break;
	case TAG_String:     //  8
	  rc = get_tag_string( f, (char**)&(n->payload) ) ;
	  break;
	case TAG_TAG_List:   //  9
	  n->payload = malloc(sizeof(rough_list));
	  rc = read_tag_list( f, n->payload );
	  break;
    case TAG_Compound:   // 10
	  n->payload = new_list();
	  rc = read_tag_compound( f, n->payload );
	  break;
	default:
	  printf( "[NT] Unhandled tag type: %i\n", n->type ) ;
	  return FALSE;
  }
  
  return rc ;
}


int get_tag_type( gzFile f, int* tag ) {
	int t = 0;
	
	int rc = gzread( f, &t, 1);
	if ( rc != 1 ) {
		printf( "GZip read error\n" ) ;
		return FALSE ;
	}

	//printf( "[TT] %i\n", t ) ;

	*tag = t ;
	
	return TRUE ;	
}


int get_named_tag( gzFile f, Named_Tag *n ) {
	int type;
	char* name = NULL;
	
	int rv = get_tag_type( f, &type ) ;
	if ( rv != TRUE ) { printf( "[NT] error: short\n" ) ; return FALSE ; }

  if ( type != TAG_End ) {
	  rv = get_tag_string( f, &name ) ;
	  if ( rv != TRUE ) { printf( "[NT] error: string\n" ) ; return FALSE ; }
  }

	n->type = type ; n->name = name ;
	
	return TRUE;
}


void NT_dispose( Named_Tag *n ) {
	free( n->name ) ;
}
