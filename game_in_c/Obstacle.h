class Obstacle
{
  public:

  i8 x;
  i8 y;
  Sprite * sp;

  Obstacle()
  {
    sp = new Sprite(2,2,obstacleText);
  }

  Rect GetRect() {
    return Rect(x, y, sp->cols, sp->rows);
  }


  ~Obstacle()
  {
    delete sp;
  }
};
