#include "viewer.h"

#include <iostream>

#include <QPainter>
#include <QSlider>

extern "C" {
#include "chunks.h"
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
    //p.save();

    // paint it!
    int topx = x_off;
    int topy = y_off;
    for ( int x = 0 ; x < 16 ; x++ ) {
        for ( int z = 0; z < 16 ; z++ ) {
            // from website:
            //   unsigned char BlockID = Blocks[ y + ( z * ChunkSizeY(=128) + ( x * ChunkSizeY(=128) * ChunkSizeZ(=16) ) ) ];
            unsigned char block = c->data[ychunk + (z*128 + (x*128*16) )];
            QColor c;

            switch (block) {
            case 0: // AIR
                break;
            case 1: // STONE
            case 4: // COBBLESTONE
            case 7: // BEDROCK
            case 14: // GOLD ORE
            case 15: // IRON ORE
            case 16: // COAL ORE
                c = Qt::black;
                break;
            case 17: // WOOD
                c = Qt::darkYellow;
                break;
            case 18: // LEAVES
                c = Qt::darkGreen;
                break;
            case 2: // GRASS
            case 3: // DIRT
                c = Qt::green;
                break;
            case 8: // WATER
            case 9: // Stationary Water
                c = Qt::blue;
                break;
            case 10: // LAVA
            case 11: // Stationary Lava
                c = Qt::red;
                break;
            case 12: // SAND
            case 13: // GRAVEL
                c = Qt::yellow;
                break;
            default:
                std::cout << "Unhandled block id: " << (int)block << std::endl;
                c = Qt::white;
            }

            //p.drawRect(topx,topy,topx+3,topy+3);
            p.fillRect(topx,topy,topx+chunk_size,topy+chunk_size,c);
            topx += chunk_size;
        }
        topy += chunk_size;
        topx = x_off;
    }

    //p.restore();
}

void Viewer::paintEvent(QPaintEvent *)
{
  if ( chunks == NULL ) return;

  QSlider* s = parentWidget()->findChild<QSlider*>("levelSlider");

  int level   = s->value();
  int delta_x = abs(max_x - min_x) ;
  int delta_z = abs(max_z - min_z) ;

  // some info
  std::cout << "map size: " << delta_x    << ", " << delta_z << std::endl;
  std::cout << "*16 size: " << delta_x*16 << ", " << delta_z*16 << std::endl;
  std::cout << "w: " << width() << " h: " << height() << std::endl;
  std::cout << "level: " << level << std::endl;

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
