// tag_byte_array.h
//
// Created: 20 OCT 2010
// Author : Daniel M. Klein
//

#include <zlib.h>

#ifndef __tag_byte_array_h
#define __tag_byte_array_h

typedef struct _byte_array {
	int length;
	unsigned char* data;
} byte_array;

int get_tag_byte_array( gzFile, byte_array* ) ;

#endif
