// main.c
//
// Created: 17 OCT 2010
// Author : Daniel M. Klein
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "common.h"
#include "named_tag.h"
#include "callbacks.h"
#include "tag_list.h"
#include "chunks.h"
#include "tag_byte_array.h"
#include "main.h"
}
#include <QtGui/QApplication>
#include "mainwindow.h"


int main( int argc, char** argv ) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
/*

  // now we read in the block data

	process_dir(argv[1]) ;

	printf( "(%i,%i) to (%i,%i)\n", min_x,min_z,max_x,max_z );

	scan_chunks();


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
        //return EXIT_SUCCESS;
}
