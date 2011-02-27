// processor.c
//
// Created: 26 FEB 2011
// Author : Daniel M. Klein
//

#include "processor.h"
#include "common.h"
#include "chunks.h"
#include "tag_byte_array.h"

#include <stdio.h>
#include <dirent.h>
#include <zlib.h>

player Player;
int  current_x = -1 ;
int  current_z = -1 ;
int  first_file    = 1;
unsigned char *current_chunk = NULL;
int max_x, max_z, min_x, min_z = -1;

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

Named_Tag* process_file( const char* c ) {
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

int set_x_position( const Named_Tag* n) {
        current_x = *(int*)n->payload;

        if ( first_file ) { max_x = current_x ; min_x = current_x ; }
        if ( current_x > max_x ) max_x = current_x ;
        if ( current_x < min_x ) min_x = current_x ;

        return TRUE ;
}

int set_z_position( const Named_Tag* n) {
        current_z = *(int*)n->payload;

        if ( first_file ) { max_z = current_z ; min_z = current_z ; }
        if ( current_z > max_z ) max_z = current_z ;
        if ( current_z < min_z ) min_z = current_z ;

        return TRUE ;
}

int save_blocks( const Named_Tag* n) {
  byte_array* b = (byte_array*)n->payload;

  printf("byte_array: %li\n", (long)b->data);
  // instead of copying the memory in, save the pointer
  current_chunk = b->data;

  b->length = 0;
  b->data    = NULL;

  return TRUE ;
}


void process_dir( const char* c ) {
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
