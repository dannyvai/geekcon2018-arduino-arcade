#pragma once

#include "Draw.h"
#include "Number.h"

#define Y_END 13


struct Life {
  u8 x;
  u8 y;
  i8 count;

  void Draw() {
    for (u8 i = 0; i < count; ++i) {
      u8 offset = i * 2;
      DrawChar(x+offset, y, '@');
      DrawChar(x+offset+1, y, '?');
    }
  }

  bool Die() {
    --count;
    if (count < 0) {
      count = 3;
    }
    return count == 0;
  }
};


bool IsIntersecting(const struct Rect& r1, const struct Rect& r2) {
  return (
      ((r1.x + r1.w) > r2.x) &&
      (r1.x < (r2.x + r2.w)) &&
      ((r1.y + r1.h) > r2.y) &&
      (r1.y < (r2.y + r2.h))) ;
    
}




char borderText[] = {'.', '.', ',', '.', ',', ';', ',', '.', ',', '.'};

struct Obstacle {
  i8 x;
  i8 y;
//  char g;

    Rect GetRect() {
    return {x, y, 2, 2};
  }
};

struct Bike {
  i8 x;
  i8 y;

    Rect GetRect() {
    return {x, (i8)(y+1), 7, 3-1};
  }
};

void DrawBike(i8 x, i8 y) {
DrawChar(x+3, y+0, '_');
DrawChar(x+4, y+0, '_');
DrawChar(x+5, y+0, 'o');
DrawChar(x+1, y+1, '_');
DrawChar(x+3, y+1, '\\');
DrawChar(x+4, y+1, '<');
DrawChar(x+5, y+1, '_');
DrawChar(x+0, y+2, '(');
DrawChar(x+1, y+2, '_');
DrawChar(x+2, y+2, ')');
DrawChar(x+3, y+2, '/');
DrawChar(x+4, y+2, '(');
DrawChar(x+5, y+2, '_');
DrawChar(x+6, y+2, ')');

}

constexpr u8 obstacleCount = 4;
struct Game {
  Bike bike {0,7};
  Obstacle obstacles[obstacleCount] = {
  };
  Life life { 26, 0, 3 };
  unsigned short score{0};

  
  int scrollIndex{0};
//  static constexpr u8 trailRows = 14;
//  static constexpr u8 trailStart = 1;
#define trailRows 14
#define trailStart 1

  Game() {
    for (auto& obstacle:obstacles) {
      obstacle.x = (rand() % 40) + 26;
      obstacle.y = (rand() % trailRows) + trailStart + 1;
//      obstacle.g = (rand() % 3) + '$';
    }
  }

  Game& operator=(const Game&) =default;

  void DrawBackground() {
      for (u8 i=0; i < TV.char_line(); ++i) {
      DrawChar(i, trailStart, borderText[(i + scrollIndex) % 10]);
    }
  }

  bool IsGameOver() {
    return (life.count == 0) || (seconds == 0);
  }

//  

  void Up() {
    --bike.y;
    if (bike.y < trailStart) {
      bike.y = trailStart;
    }
//  dir = -1;
  }

  void Down() {
    if (bike.y < Y_END)
    {
      ++bike.y;
    }
//  dir = 1;
  }

  void Straight() {
//    dir = 0;
  }

  bool prev_step_intersection = false;
  bool current_step_intersection = false;
  
  void Step() {
    score++;
    
    ++scrollIndex;
    Rect bikeRect = bike.GetRect();
    bool current_step_intersection_flag = false;
    for (auto& obstacle : obstacles) {
      --obstacle.x;
      if (obstacle.x < -5) {
        obstacle.x = TV.char_line() + (rand() % 15);
        obstacle.y = (rand() % trailRows) + trailStart + 1;
//        obstacle.g = (rand() % 3) + '$';
      }

      if (IsIntersecting(bikeRect, obstacle.GetRect())) {
        current_step_intersection_flag = true;
      }
    }
    
    if (current_step_intersection_flag)
    {
      if (!prev_step_intersection)
      {
        life.Die();
        Serial.write("b");
        prev_step_intersection = true;
      }
    } else {
      prev_step_intersection = false;
    }
  }


  void Draw() {
    DrawBackground();
    for (auto& obstacle : obstacles) {
//      DrawChar(obstacle.x, obstacle.y, obstacle.g);
      DrawChar(obstacle.x, obstacle.y, '#');
      DrawChar(obstacle.x+1, obstacle.y, '&');
      DrawChar(obstacle.x+1, obstacle.y+1, '%');
      DrawChar(obstacle.x, obstacle.y+1, '$');
    }
    
    DrawBike(bike.x, bike.y);
    if (prev_step_intersection) {
      DrawChar(10+0, 10+0, 'B');
      DrawChar(10+1, 10+0, 'O');
      DrawChar(10+2, 10+0, 'O');
      DrawChar(10+3, 10+0, 'M');
      DrawChar(10+4, 10+0, '!');

    }
    DrawNumber(20, 0, 4, score);
    life.Draw();

  DrawChar(0, 0, 'B');
  DrawChar(1, 0, 'i');
  DrawChar(2, 0, 'k');
  DrawChar(3, 0, 'e');

  DrawChar(5, 0, 'o');
  DrawChar(6, 0, 'f');
  
  DrawChar(8, 0, 'D');
  DrawChar(9, 0, 'E');
  DrawChar(10, 0, 'A');
  DrawChar(11, 0, 'T');
  DrawChar(12, 0, 'H');

  
  DrawChar(14, 0, ((seconds / 600) % 10)+'0');
  DrawChar(15, 0, ((seconds / 60) % 10)+'0');
  DrawChar(16, 0, ':');
  DrawChar(17, 0, ((seconds % 60) / 10)+'0');
  DrawChar(18, 0, (seconds % 10)+'0');
  }
};
