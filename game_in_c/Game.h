
class Game
{
    private:
      u8 trailRows = 14;
      u8 trailStart;
      u8 scrollIndex;
      Sprite * chr;
      u8 chr_x;
      u8 chr_y;
      
      u8 life_count = 3;      
      u8 life_x = 26;
      u8 life_y = 0;

      Obstacle obstacles[NUM_OBSTACLES];
    public:
      Game(Sprite * s)
      {
        chr = s;
        trailStart = 0;
        scrollIndex = 0;
        chr_x = 0;
        chr_y = 2;

        for(int i=0; i<NUM_OBSTACLES; i++)
        {
          //obstacles[i] = new Obstacle();
          obstacles[i].x = (rand() % 30) + 5;
          obstacles[i].y = (rand() % trailRows) + trailStart + 1;
          //Serial.println(obstacles[i].x);
        }
        
      }
      
    void DrawBackground(TVout tv) {
        for (u8 i=0; i < tv.char_line(); ++i) {
        DrawChar(tv,i, trailStart, borderText[(i + scrollIndex) % 10]);
      }
    } 
       
    void DrawCharacter(TVout tv)
    {
        DrawSprite(tv,chr_x, chr_y,chr);
    }

    void DrawObstacles(TVout tv)
    {
      for(int i=0; i<NUM_OBSTACLES; i++)
      {
        DrawSprite(tv,obstacles[i].x, obstacles[i].y,obstacles[i].sp);
      }
    }


    void DrawLife(TVout tv) {
      for (u8 i = 0; i < life_count; ++i) {
        u8 offset = i * 2;
        DrawChar(tv,life_x+offset, life_y, '@');
        DrawChar(tv,life_x+offset+1, life_y, '?');
      }
    }


    void Step(TVout tv)
    {
      DrawBackground(tv);
      DrawLife(tv);
      DrawCharacter(tv);
      DrawObstacles(tv);
      scrollIndex++;
    }
};
