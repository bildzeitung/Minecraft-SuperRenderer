// processor.h
//
// Created: 26 FEB 2011
// Author : Daniel M. Klein
//

#ifndef __processor_h__
#define __processor_h__

#include "named_tag.h"
#include "tag_list.h"
#include "player.h"

extern player Player;
extern int  current_x;
extern int  current_z;
extern int  first_file;
extern unsigned char *current_chunk;
extern int max_x, max_z, min_x, min_z;


int position( const Named_Tag*) ;
Named_Tag* process_file( const char* ) ;
void process_dir( const char* ) ;

int set_x_position( const Named_Tag* ) ;
int set_z_position( const Named_Tag* );
int save_blocks( const Named_Tag* );

#endif
