#pragma once

#include "snake.h"
#include "world.h"

class Game
{
public:
  Game();
  ~Game();

  void checkEvents();
  void checkInput();
  void update();
  void draw();
  bool isDone() const { return isDone_; }

private:
  int segmentSize_;
  Snake snake_;
  World world_;
  sf::RenderWindow renderWindow_;
  bool isDone_;
};
