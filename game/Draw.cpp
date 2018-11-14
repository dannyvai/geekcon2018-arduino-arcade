#include "Draw.h"
#include <string.h>


void SetupDraw()  {
  TV.begin(PAL);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font4x6);
}

void DrawChar(i8 x, i8 y, char c) {
  if (x < 0) { return; }
  if (y < 0) { return; }
  if (x >= TV.char_line()) { return; }
  if (y > 25) { return; }

  TV.print_char(x * FONT_WIDTH, y * FONT_HEIGHT, c);
}

void Sprite::Draw(i8 x, i8 y) {
  //char temp_data[20];
  for (u8 row = 0; row < rows; ++row) {  
    for (u8 col = 0; col < cols; ++col) { 
      DrawChar(x+col, y+row, data[(row*cols) + col]);
    }
    //memcpy(temp_data,data[(row*cols)],cols);
    //temp_data[cols] = 0;
    //TV.println(x*FONT_WIDTH,y*FONT_HEIGHT,temp_data);
  }
}
