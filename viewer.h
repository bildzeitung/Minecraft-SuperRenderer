#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>

class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);

signals:

public slots:

protected:
     void paintEvent(QPaintEvent *);
     void draw_chunk( int, int, int, int, int);
};

#endif // VIEWER_H
