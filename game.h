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
  void restartClock();

private:
  int segmentSize_;
  
  Snake snake_;
  World world_;
  sf::RenderWindow renderWindow_;
  bool isDone_;
  float elapsedTime_;  // time passed since the game starts
  sf::Clock clock_;

  sf::Text statusBar_;
  sf::Text title_;
  sf::Font font_;

  void initializeStatusBar();
  void updateStatusBar();
};
