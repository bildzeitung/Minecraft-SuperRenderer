// main.c
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <dirent.h>
#include <string.h>

#include "common.h"
#include "named_tag.h"
#include "callbacks.h"
#include "player.h"
#include "tag_list.h"
#include "chunks.h"
#include "tag_byte_array.h"
#include "main.h"


player Player;

int max_x, max_z, min_x, min_z = -1;

int  first_file    = 1;
int  current_x     = -1 ;
int  current_z     = -1 ;
char current_chunk[BLOCKSIZE];


Named_Tag* process_file( char* c ) {
	gzFile f = gzopen( c, "r") ;	
	if ( !f ) { printf( "Bad filename\n" ) ; return NULL;}

	//printf("File: %s\n",c);

	Named_Tag* tag = NT_new();	
	int rv = read_named_tag( f, tag ) ;	
	if ( !rv ) { printf( "[main] Could not get tag\n" ) ; return NULL;}	
	
	//print_named_tag( tag ) ;
	//printf("\n");
	
	// clean up
	gzclose(f);
	
	return tag;
}

void process_dir( char* c ) {
	//printf("Processing %s\n", c) ;
	DIR* d = opendir( c ) ;

	struct dirent* e;
	while (  (e=readdir(d)) ) {
		// skip dot, dot-dot
		if ( !strcmp(e->d_name,"." ) ) continue;
		if ( !strcmp(e->d_name,".." ) ) continue;
		// skip player info
		if ( !strcmp(e->d_name,"level.dat" ) ) continue;
		// only directories and .dat files
		
		if ( e->d_type == DT_DIR ) {
			int len = strlen(c) + 1 + strlen(e->d_name) + 1 ;
			char *f = (char*)malloc(sizeof(char)*len);
			strcpy(f,c);
			strcat(f,"/");
			strcat(f,e->d_name);
			process_dir(f);
			free(f);
			continue;
		}
		
		if ( !strstr(e->d_name+strlen(e->d_name)-4, ".dat" )) continue ;
		
		// ok, we have a file to process
		char* fname = (char*)malloc(sizeof(char)*(strlen(c)+strlen(e->d_name)+2));
		strcpy(fname,c) ; strcat(fname,"/") ; strcat(fname,e->d_name);
		Named_Tag* n = process_file(fname);
		first_file = 0 ;
	  //print_named_tag( n ) ;
	  //printf("\n");

		//printf("%s: %i %i\n", fname, current_x, current_z) ;
		add_chunk( current_x, current_z, current_chunk ) ;

	  free(fname);
		NT_dispose(n);
		//printf("%s\n", e->d_name ) ;
	}
	
	closedir(d);
}

int position( const Named_Tag* n) {
	rough_list* p = (rough_list*)n->payload;
		
	Player.x = *((double*)p->payload[0]);
	Player.y = *((double*)p->payload[1]);
	Player.z = *((double*)p->payload[2]);
	
	//print_named_tag(n) ;	
	printf( "Player co-ordinates: (%f, %f, %f)\n", 
	        Player.x, Player.y, Player.z
	      );
		
	return TRUE;
}

int set_x_position( const Named_Tag* n) {
	current_x = *(int*)n->payload;
	
	if ( first_file ) { max_x = current_x ;	min_x = current_x ; }
	if ( current_x > max_x ) max_x = current_x ;
	if ( current_x < min_x ) min_x = current_x ;
	
	return TRUE ;
}

int set_z_position( const Named_Tag* n) {
	current_z = *(int*)n->payload;	

	if ( first_file ) { max_z = current_z ;	min_z = current_z ; }
	if ( current_z > max_z ) max_z = current_z ;
	if ( current_z < min_z ) min_z = current_z ;
	
	return TRUE ;	
}

int save_blocks( const Named_Tag* n) {
	byte_array* b = n->payload;
	memcpy(current_chunk,b->data,BLOCKSIZE);
	return TRUE ;	
}


int main( int argc, char** argv ) {
	if ( argc < 2 ) {
		printf( "Need a directory\n" ) ;
		return EXIT_FAILURE;
	}

	register_named_tag( "Pos", &position ) ;

	char* d = "/level.dat" ;
	int l = strlen(argv[1]) + strlen(d) + 1;
	char *level = (char*)(malloc(l*sizeof(char)));
	strcpy(level,argv[1]); strcat(level, d) ;
	Named_Tag* level_tag = process_file(level);
	NT_dispose(level_tag);

	unregister_named_tag( "Pos" ) ;

  // now we read in the block data
	register_named_tag( "xPos",   set_x_position ) ;
	register_named_tag( "zPos",   set_z_position ) ;
	register_named_tag( "Blocks", save_blocks    ) ;

	process_dir(argv[1]) ;

	printf( "(%i,%i) to (%i,%i)\n", min_x,min_z,max_x,max_z );

	scan_chunks();

/*
	gzFile f = gzopen( argv[1], "r") ;	
	if ( !f ) { printf( "Bad filename\n" ) ; return EXIT_FAILURE ;}

	Named_Tag tag;	
	int rv = read_named_tag( f, &tag ) ;	
	if ( !rv ) { printf( "[main] Could not get tag\n" ) ; return EXIT_FAILURE ;}
	
	// we expect the file to start with a compound tag
	if ( tag.type != TAG_Compound ) {
		printf( "Expected compound tag\n" ) ;
		return EXIT_FAILURE;
	}
	
	print_named_tag( &tag ) ;
*/
	return EXIT_SUCCESS;
}
