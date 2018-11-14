#define FONT_WIDTH  4
#define FONT_HEIGHT 6
#define NUM_OBSTACLES 2

typedef unsigned char u8;
typedef signed char i8;

class Rect {
  i8 x;
  i8 y;
  u8 w;
  u8 h;
  public:
  Rect(i8 xx,i8 yy, u8 ww,u8 hh)
  {
    x = xx;
    y = yy;
    w = ww;
    h = hh;
    
  }
};
