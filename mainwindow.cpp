#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <iostream>

extern "C" {
#include "callbacks.h"
#include "processor.h"
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString dirName = QFileDialog::getExistingDirectory(this,"Save directory");
    if (!dirName.isEmpty()) load(dirName);
}

void MainWindow::load(const QString &dirName)
{
    curDir = dirName;

    // get where the player is
    register_named_tag( "Pos", &position ) ;

    QString level(curDir + "/level.dat");
    Named_Tag* level_tag = process_file(level.toStdString().c_str());
    NT_dispose(level_tag);
    unregister_named_tag( "Pos") ;

    // load in the block data
    register_named_tag( "xPos",   set_x_position ) ;
    register_named_tag( "zPos",   set_z_position ) ;
    register_named_tag( "Blocks", save_blocks    ) ;

    process_dir(curDir.toStdString().c_str()) ;
}
