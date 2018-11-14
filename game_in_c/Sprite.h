#include "BasicDraw.h"

class Sprite{
  public:
    u8 cols;
    u8 rows;
    char* data;
    
    Sprite(i8 c,i8 r, char* d)
    {
      cols = c;
      rows = r;
      data = d;
    }
};

void DrawSprite(TVout tv,i8 x, i8 y,Sprite * s)
{
    for (u8 row = 0; row < s->rows; ++row) {  
        for (u8 col = 0; col < s->cols; ++col) { 
            DrawChar(tv,x+col, y+row, s->data[(row*s->cols) + col]);
        }
    }
}
