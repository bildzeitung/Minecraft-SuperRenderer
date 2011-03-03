// chunks.c
//
// Created: 19 FEB 2011
// Author : Daniel M. Klein
//

#include "chunks.h"
#include <QColor>
#include <iostream>

chunk_t* chunks = NULL ;
int key_len     = -1;

void add_chunk( int x, int z, unsigned char* d ) {
  // prep
  chunk_t* c = (chunk_t*)malloc(sizeof(chunk_t));
  memset(c,0,sizeof(chunk_t));

  // configure
  memcpy(c->data,d,BLOCKSIZE);
  c->xPos = x ; c->zPos = z;

  // create 16x16 pixmaps for each layer
  for ( int y = 0 ; y < 128 ; y++ ) {
      c->idata[y] = QImage(16,16,QImage::Format_ARGB32_Premultiplied);

      for ( int x = 0 ; x < 16 ; x++ ) {
          QRgb *scan = (QRgb*)(c->idata[y].scanLine(x));

          for ( int z = 0; z < 16 ; z++) {
              QColor color ;

              // from website:
              //   unsigned char BlockID = Blocks[ y + ( z * ChunkSizeY(=128) + ( x * ChunkSizeY(=128) * ChunkSizeZ(=16) ) ) ];
              switch (c->data[y + (z*128 + (x*2048) )]) {
              case 0: // AIR
                  break;
              case 1: // STONE
              case 4: // COBBLESTONE
              case 7: // BEDROCK
              case 14: // GOLD ORE
              case 15: // IRON ORE
              case 16: // COAL ORE
                  color = Qt::black;
                  break;
              case 17: // WOOD
                  color = Qt::darkYellow;
                  break;
              case 18: // LEAVES
                  color = Qt::darkGreen;
                  break;
              case 2: // GRASS
              case 3: // DIRT
                  color = Qt::green;
                  break;
              case 8: // WATER
              case 9: // Stationary Water
                  color = Qt::blue;
                  break;
              case 10: // LAVA
              case 11: // Stationary Lava
                  color = Qt::red;
                  break;
              case 12: // SAND
              case 13: // GRAVEL
                  color = Qt::yellow;
                  break;
              default:
                  //std::cout << "Unhandled block id: " << (int)block << std::endl;
                  color = Qt::white;
              }

              scan[z]   = color.rgb();
          }
      }
  }

  key_len = offsetof(chunk_t,zPos)
                + sizeof(int) - offsetof(chunk_t,xPos);
	
  // add
  HASH_ADD( hh, chunks, xPos, key_len, c);

  std::cout << "Done chunk: " << x << ", " << z << std::endl;
}
