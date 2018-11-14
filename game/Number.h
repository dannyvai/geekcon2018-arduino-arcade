#pragma once

#include "Draw.h"
#include <stdio.h>


void DrawNumber(i8 x, i8 y, u8 width, unsigned int value) {
  for (int temp = value, i = width - 1; i >= 0; --i) {
//    char digit;
//    switch (temp % 10) {
//      case 0: digit = '0'; break;
//      case 1: digit = '1'; break;
//      case 2: digit = '2'; break;
//      case 3: digit = '3'; break;
//      case 4: digit = '4'; break;
//      case 5: digit = '5'; break;
//      case 6: digit = '6'; break;
//      case 7: digit = '7'; break;
//      case 8: digit = '8'; break;
//      case 9: digit = '9'; break;
//  }
  DrawChar(x+i, y, (((unsigned int)temp)%10)+'0');
  temp /= 10;
  }
}
