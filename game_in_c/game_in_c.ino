#include <TVout.h>
#include <fontALL.h>
#include <stdlib.h>

#include "Types.h"
#include "Const.h"
#include "Sprite.h"
#include "Obstacle.h"
#include "Game.h"


TVout TV;

const int handlebars_pin = A0 ;


u8 stepsToPerform;

void StepInterrupt() {
    Serial.println("WTF");
    ++stepsToPerform;
}

const int lEncoder = 2;    // interrupt 0   

void SetupDraw()  {
  TV.begin(PAL);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font4x6);
}

void setup()  {
    Serial.begin(9600);
  
    stepsToPerform = 0;

    //Bike encoder
    //digitalWrite(lEncoder,1);
    //attachInterrupt(0,StepInterrupt,CHANGE);

    SetupDraw();
}



int btn_up_res,btn_dwn_res,handlebars_val;



Sprite * bike = new Sprite(7,3,bikeSprite);
Sprite * swimmer = new Sprite(9,3,swimmerSprite);
Game game(bike);

void loop() {

    handlebars_val = analogRead(handlebars_pin);
    /*
    if(handlebars_val > 550) {
        game->Up();
    } else if(handlebars_val < 450) {
        game->Down();
    }*/
    
    TV.clear_screen();
    game.Step(TV);
    TV.delay(40);

}
