#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "viewer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void open();

private:
    Ui::MainWindow *ui;
    Viewer *v;

    QString curDir;

    void load(const QString &);
};

#endif // MAINWINDOW_H
