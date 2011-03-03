#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSlider>

#include <iostream>

#include "viewer.h"

extern "C" {
#include "callbacks.h"
}

#include "processor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFrame *f = new QFrame(this);

    v = new Viewer(this);

    QHBoxLayout *l = new QHBoxLayout(f);
    f->setLayout(l);
    l->addWidget(v);

    QSlider *s = new QSlider(Qt::Vertical,f);
    s->setObjectName("levelSlider");
    s->setMinimum(0);
    s->setMaximum(127);
    s->setSingleStep(1);

    l->addWidget(s);

    setCentralWidget(f);

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(s,SIGNAL(valueChanged(int)),v,SLOT(repaint()));
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

    // set the initial height to where the player is
    QSlider *s = findChild<QSlider*>("levelSlider");
    s->setValue((int)Player.y);

    // load in the block data
    register_named_tag( "xPos",   set_x_position ) ;
    register_named_tag( "zPos",   set_z_position ) ;
    register_named_tag( "Blocks", save_blocks    ) ;

    process_dir(curDir.toStdString().c_str()) ;

    std::cout << "Load complete" << std::endl;

    repaint();
}
