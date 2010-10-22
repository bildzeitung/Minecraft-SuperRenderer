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

void print_list(list*, int) ;

void _print_named_tag( Named_Tag* n, int indent_in ) {
	size_t indent_s = ((indent_in*2)+1)*sizeof(char);
	char *indent = (char*)malloc(indent_s);
	memset(indent,' ',indent_s);
	indent[indent_in*2] = '\0';
	
  //for ( int i = 0; i < indent ; i++ ) printf("  ") ;
	printf("%s",indent);

  switch ( n->type ) {
	  case TAG_Short:   // 2
	    printf( "TAG_Short(\"%s\"): %i\n", n->name, *((short*)n->payload));
	    break;
		case TAG_Int:     // 3
			printf( "TAG_Int(\"%s\"): %i\n", n->name, *((int*)n->payload));
			break;
	  case TAG_Long:    // 4
		  printf( "TAG_Long(\"%s\"): %li\n", n->name, *((long*)n->payload));
		  break;
	  case TAG_Float:   // 5
			printf( "TAG_Float(\"%s\"): %f\n", n->name, *((float*)n->payload));
			break;
		case TAG_Double:  // 6
	    printf( "TAG_Double(\"%s\"): %.15f\n", n->name, *((double*)n->payload));
	    break;		
		case TAG_String:  // 8
			printf( "TAG_String(\"%s\"): %s\n", n->name, (char*)n->payload );
			break;
    case TAG_Compound:
			printf( "Tag_Compound(\"%s\"): %i entries\n%s{\n", 
					    n->name, ((list*)(n->payload))->count, indent 
					  ) ;
			print_list( n->payload, indent_in+1 ) ;
			printf( "%s}\n", indent ) ;
			break;
	  default:
	    printf( "[PT] Unhandled tag type: %i\n", n->type ) ;
  }  

	free(indent);
}

void print_list( list* l, int indent ) {
  while ( l->next != NULL ) {
	_print_named_tag( l->data, indent ) ;
	l = l->next ;
  }
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
	  rc = get_tag_byte_array( f, &(n->payload) );
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
