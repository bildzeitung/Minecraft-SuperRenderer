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
#include "tag_byte_array.h"
#include "main.h"
}
#include <QtGui/QApplication>
#include "chunks.h"
#include "mainwindow.h"


int main( int argc, char** argv ) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
