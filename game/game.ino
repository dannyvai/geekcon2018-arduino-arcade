#include <TVout.h>
#include <fontALL.h>
#include <stdlib.h>
#include <EEPROM.h>



int seconds{60};

#include "Draw.h"
#include "Game.h"


TVout TV;

const int button_up_pin = 5;
const int button_down_pin = 4;
const int handlebars_pin = A0 ;


using u8 = unsigned char;
using i8 = signed char;
const byte interruptPin = 2;
u8 stepsToPerform;



unsigned short highscore = 0;
u8 milliCounter;
unsigned long secondCounter;
  
void setup()  {
  Serial.begin(9600);

  pinMode(button_up_pin,INPUT_PULLUP);
  pinMode(button_down_pin,INPUT_PULLUP);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), StepInterrupt, CHANGE);

  
  SetupDraw();

  stepsToPerform = 0;

  milliCounter = 0;
  secondCounter = 0;

//  highscore = (EEPROM.read(0)) || EEPROM.read(1);
     EEPROM.get(0, highscore);
//EEPROM.put(0, 0);
}


Game * game = new Game();


//int btn_up_res,btn_dwn_res,handlebars_val;

constexpr auto TV_HEIGHT = 16;




void StepInterrupt() {
  ++stepsToPerform;
}



void MyDelay() {
unsigned long time = millis() + 15;
        while(millis() < time);

}

void DrawGameOver() {
  DrawChar(12+0, 8+0, 'G');
  DrawChar(12+1, 8+0, 'a');
  DrawChar(12+2, 8+0, 'm');
  DrawChar(12+3, 8+0, 'e');
  DrawChar(12+5, 8+0, 'O');
  DrawChar(12+6, 8+0, 'v');
  DrawChar(12+7, 8+0, 'e');
  DrawChar(12+8, 8+0, 'r');

  DrawChar(10+2, 10, 'Y');
  DrawChar(10+3, 10, 'o');
  DrawChar(10+4, 10, 'u');
}

void DrawMenu() {
//DrawChar(9+4, 5+0, 'W');
//DrawChar(9+5, 5+0, 'e');
//DrawChar(9+6, 5+0, 'l');
//DrawChar(9+7, 5+0, 'c');
//DrawChar(9+8, 5+0, 'o');
//DrawChar(9+9, 5+0, 'm');
//DrawChar(9+10, 5+0, 'e');
//DrawChar(9+12, 5+0, 't');
//DrawChar(9+13, 5+0, 'o');
DrawChar(9+0, 5+2, '@');
DrawChar(9+1, 5+2, '?');
DrawChar(9+2, 5+2, 'B');
DrawChar(9+3, 5+2, 'i');
DrawChar(9+4, 5+2, 'k');
DrawChar(9+5, 5+2, 'e');
DrawChar(9+7, 5+2, 'o');
DrawChar(9+8, 5+2, 'f');
DrawChar(9+10, 5+2, 'D');
DrawChar(9+11, 5+2, 'E');
DrawChar(9+12, 5+2, 'A');
DrawChar(9+13, 5+2, 'T');
DrawChar(9+14, 5+2, 'H');
DrawChar(9+15, 5+2, '@');
DrawChar(9+16, 5+2, '?');
DrawChar(9+4, 5+4, 'P');
DrawChar(9+5, 5+4, 'e');
DrawChar(9+6, 5+4, 'd');
DrawChar(9+7, 5+4, 'a');
DrawChar(9+8, 5+4, 'l');
DrawChar(9+10, 5+4, 't');
DrawChar(9+11, 5+4, 'o');
DrawChar(9+5, 5+5, 'S');
DrawChar(9+6, 5+5, 't');
DrawChar(9+7, 5+5, 'a');
DrawChar(9+8, 5+5, 'r');
DrawChar(9+9, 5+5, 't');
}

void DrawHighscore() {
  
      DrawChar(8+4, 12, 'B');
      DrawChar(9+4, 12, 'e');
      DrawChar(10+4, 12, 's');
      DrawChar(11+4, 12, 't');
      DrawNumber(13+4, 12, 4, highscore);
}

enum class State : u8 {Menu, Game, GameOver};
State state = State::Menu;
constexpr u8 pedalsToStart = 25;
constexpr u8 gameOverSeconds = 10;
constexpr u8 gameRuntime = 60;
u8 menuSteps = pedalsToStart;
//u8 gameoverLeft = gameOverSeconds;
u8 treeCount = 0;
void loop() {
  int handlebars_val = analogRead(handlebars_pin);
//  Serial.println(handlebars_val);
//
  if (stepsToPerform) {
    --stepsToPerform;
    
  if (state == State::Game) {
      if(++treeCount == 3) {
        Serial.write("f");
        treeCount = 0;
      }
  }

    if (state == State::Game) {
      if(handlebars_val > 630) {
         game->Up();
      } else if(handlebars_val < 490) {
         game->Down();
      } 
      game->Step();
    }

    if (state == State::Menu) {
      menuSteps--;
      if (menuSteps == 0) { 
        Serial.write("nnnn");
        state = State::Game;
        delete game;
        game = new Game();
        seconds = gameRuntime;
      }
    } 
    
  }
  if ((state == State::GameOver) && (seconds == 0)) {
      state = State::Menu;
      menuSteps = pedalsToStart;
    }
  
  TV.clear_screen();
//  Serial.println((u8)state);

  switch (state) {
    case State::Menu: {
      DrawMenu();
      DrawHighscore();
      break;
    }
    case State::Game: {
      game->Draw();
      break;
    }
    case State::GameOver: {
      DrawGameOver();
      DrawNumber(17, 10, 4, game->score);
      if (game->score > highscore) {
        highscore = game->score;
        
        EEPROM.put(0, highscore);
      }
      DrawHighscore();
      break;
    }
  }
  
  if (game->IsGameOver() && (state == State::Game)) {
    state = State::GameOver;
//    menuSteps = pedalsToStart;
    Serial.write("dddd");
    seconds = gameOverSeconds;
  }
//  Serial.println(milliCounter);
  milliCounter += 1;
  if (milliCounter > 25) {
    milliCounter = 0;
    seconds--;
//    gameoverLeft--;
  }

MyDelay();
}
