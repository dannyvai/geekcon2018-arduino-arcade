#pragma once

#include <TVout.h>
#include <fontALL.h>
#include <stdlib.h>

using u8 = unsigned char;
using i8 = signed char;

extern TVout TV;


void SetupDraw();

const u8 FONT_WIDTH = 4;
const u8 FONT_HEIGHT = 6;



void DrawChar(i8 x, i8 y, char c);

struct Sprite {
  u8 cols;
  u8 rows;
  char* data;

  Sprite(u8 width, u8 height, char* data):cols(width),rows(height),data(data) {}

  void Draw(i8 x, i8 y);
};

struct Rect {
  i8 x;
  i8 y;
  u8 w;
  u8 h;
};
