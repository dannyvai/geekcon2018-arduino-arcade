
//void DrawChar(i8 x, i8 y, char c);

void DrawChar(TVout tv,i8 x, i8 y, char c) {
  if (x < 0) { return; }
  if (y < 0) { return; }
  if (x >= tv.char_line()) { return; }
  if (y > 25) { return; }

  tv.print_char(x * FONT_WIDTH, y * FONT_HEIGHT, c);
}
