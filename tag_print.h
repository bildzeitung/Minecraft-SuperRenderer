// tag_print.h
//
// Created: 25 OCT 2010
// Author : Daniel M. Klein
//

#include "named_tag.h"

#ifndef __tag_print_h
#define __tag_print_h

typedef void(*print_tag_fn)(const Named_Tag*, int) ;

void print_TAG_End       ( const Named_Tag*, int) ;
void print_TAG_Byte      ( const Named_Tag*, int) ;
void print_TAG_Short     ( const Named_Tag*, int) ;
void print_TAG_Int       ( const Named_Tag*, int) ;
void print_TAG_Long      ( const Named_Tag*, int) ;
void print_TAG_Float     ( const Named_Tag*, int) ;
void print_TAG_Double    ( const Named_Tag*, int) ;
void print_TAG_Byte_Array( const Named_Tag*, int) ;
void print_TAG_String    ( const Named_Tag*, int) ;
void print_TAG_List      ( const Named_Tag*, int) ;
void print_TAG_Compound  ( const Named_Tag*, int) ;

extern print_tag_fn print_fns[];

void _print_named_tag( const Named_Tag*, int ) ;

#endif
