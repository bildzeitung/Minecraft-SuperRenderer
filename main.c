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
#include "main.h"


player Player;

/*
#define BLOCKSIZE 32768

int     bnum = 100;
char *blocks ;
int  *blockx ;
int  *blocky ;
*/


void process_file( char* c ) {
	gzFile f = gzopen( c, "r") ;	
	if ( !f ) { printf( "Bad filename\n" ) ; return ;}

	printf("File: %s\n",c);

	Named_Tag* tag = NT_new();	
	int rv = read_named_tag( f, tag ) ;	
	if ( !rv ) { printf( "[main] Could not get tag\n" ) ; return ;}	
	
	//print_named_tag( tag ) ;
	//printf("\n");
	
	// clean up
	gzclose(f);
	NT_dispose(tag);
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
		process_file(fname);
	  free(fname);
	
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
	printf("(%f, %f, %f)\n", Player.x, Player.y, Player.z);
		
	return TRUE;
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
	process_file(level);

	unregister_named_tag( "Pos" ) ;

  // pretend that 100 blocks is good enough to start
	//blocks = (char*)(malloc(sizeof(char)*bnum*BLOCKSIZE));
	//blockx = (int*)(malloc(sizeof(int)*bnum));
	//blocky = (int*)(malloc(sizeof(int)*bnum));

	process_dir(argv[1]) ;

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
