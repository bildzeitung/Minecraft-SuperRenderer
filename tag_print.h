// tag_print.h
//
// Created: 25 OCT 2010
// Author : Daniel M. Klein
//

#include "named_tag.h"

#ifndef __tag_print_h
#define __tag_print_h

typedef void(*print_tag_fn)(Named_Tag*, int) ;

void print_TAG_End       ( Named_Tag*, int) ;
void print_TAG_Byte      ( Named_Tag*, int) ;
void print_TAG_Short     ( Named_Tag*, int) ;
void print_TAG_Int       ( Named_Tag*, int) ;
void print_TAG_Long      ( Named_Tag*, int) ;
void print_TAG_Float     ( Named_Tag*, int) ;
void print_TAG_Double    ( Named_Tag*, int) ;
void print_TAG_Byte_Array( Named_Tag*, int) ;
void print_TAG_String    ( Named_Tag*, int) ;
void print_TAG_List      ( Named_Tag*, int) ;
void print_TAG_Compound  ( Named_Tag*, int) ;

extern print_tag_fn print_fns[];

void _print_named_tag( Named_Tag*, int ) ;

#endif
