#pragma once

#include "snake.h"
#include "world.h"

class Game
{
public:
  Game();

  void update();
  void draw();
  bool isDone() const { return isDone_; }

private:
  int segmentSize_;
  World world_;
  Snake snake_;
  sf::RenderWindow renderWindow_;
  bool isDone_;
};
