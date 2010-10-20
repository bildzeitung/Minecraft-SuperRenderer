// tag_list.c
//
// Created: 20 OCT 2010
// Author : Daniel M. Klein
//

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#include "tag_byte.h"
#include "tag_short.h"
#include "tag_int.h"
#include "tag_long.h"
#include "tag_float.h"
#include "named_tag.h"
#include "tag_string.h"
#include "tag_list.h"
#include "tag_compound.h"


int read_tag_list( gzFile f, rough_list* l ) {
	int rc;

	rc = get_tag_type(f, &(l->type));	
	if (!rc) {
		printf( "[TL] cannot get list type\n" ) ;
		return FALSE;
	}
	
	rc = get_tag_int(f, &(l->length) );
	if (!rc) {
		printf( "[TL] cannot get list length\n" ) ;
		return FALSE;
	}
	
	//printf( "[TL] # of entries: %i\n", l->length ) ; 
	//printf( "[TL] type        : %i\n", l->type ) ;
	
	l->payload = (void**)(malloc(sizeof(void*)*l->length));	
	for (int i = 0 ; i < l->length ; i++) {
		switch (l->type) {
			case TAG_Byte:       //  1
				rc = get_tag_byte( f, l->payload[i] );
				break ;
			case TAG_Short:      //  2
				l->payload[i] = malloc(sizeof(short));
				rc = get_tag_short( f, l->payload[i] ) ;
				break;
			case TAG_Int:        //  3
				l->payload[i] = malloc(sizeof(int));
				rc = get_tag_int( f, l->payload[i] ) ;
				break;
			case TAG_Long:       //  4
				l->payload[i] = malloc(sizeof(long));
				rc = get_tag_long( f, l->payload[i] ) ;
				break;
			case TAG_Float:      //  5
				l->payload[i] = malloc(sizeof(float));
				rc = get_tag_float( f, l->payload[i] ) ;
				break;
			case TAG_Double:     //  6
				printf( "[TL] unhandled type 6\n" ) ;
				return FALSE;
			case TAG_Byte_Array: //  7
				printf( "[TL] unhandled type 7\n" ) ;
				return FALSE;
			case TAG_String:     //  8
				rc = get_tag_string( f, (char**)&(l->payload[i]) ) ;
				break;
			case TAG_TAG_List:   //  9
				printf( "[TL] unhandled type 9\n" ) ;
				return FALSE;
			case TAG_Compound:   // 10
				l->payload[i] = new_list();
				rc = read_tag_compound( f, l->payload[i] );
				break;
			default:
				printf( "[TL] cannot process this type\n" ) ;
				return FALSE;
		}
		if ( !rc ) {
			printf( "[TL] could not process list entry\n" ) ;
			return FALSE;
		}
	}
	
	return TRUE;
}
