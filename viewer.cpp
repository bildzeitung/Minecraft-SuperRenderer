#include "viewer.h"

#include <iostream>

#include <QPainter>
#include <QSlider>

#include "chunks.h"

extern "C" {
#include "processor.h"
}

Viewer::Viewer(QWidget *parent) :
    QWidget(parent)
{
    chunk_size = 3;
}

void Viewer::draw_chunk( int xchunk, int zchunk, int ychunk, int x_off, int y_off )
{
    chunk_t *c = NULL;
    chunk_lookup l;

    l.xPos = xchunk; l.zPos = zchunk;

    HASH_FIND(hh,chunks,&l.xPos,key_len,c);

    // some chunks may not exist -- do nothing
    if ( !c ) return;

    QPainter p(this);
    p.drawImage(x_off,y_off,c->idata[ychunk].scaled(16*chunk_size,16*chunk_size));
}

void Viewer::paintEvent(QPaintEvent *)
{
  if ( chunks == NULL ) return;

  QSlider* s = parentWidget()->findChild<QSlider*>("levelSlider");

  int level   = s->value();

  // some info
  //std::cout << "map size: " << delta_x    << ", " << delta_z << std::endl;
  //std::cout << "level: " << level << std::endl;

  int x_offset = 0 ;
  int y_offset = 0 ;
  int inc = chunk_size * 16;

  for ( int i = min_x ; (i < max_x) && (x_offset<width()); i++ ) {
      for ( int j = min_z ; (j < max_z) && (y_offset<height()) ; j++ ) {
          draw_chunk(i,j, level, x_offset, y_offset);
          x_offset += inc;
      }
      y_offset += inc;
      x_offset = 0;
  }
}
