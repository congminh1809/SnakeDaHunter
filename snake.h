#pragma once

#include <SFML/Graphics.hpp>

struct SnakeSegment
{
  SnakeSegment(const int x, const int y)
    : position{ x, y }
  {}

  sf::Vector2i position;
};

using SnakeBody = std::vector<SnakeSegment>;

enum class Direction
{
  None,   // no movement
  Up,     // moving up
  Right,  // moving right
  Down,   // moving down
  Left    // moving left
};

class Snake
{
public:
  Snake(const int segmentSize, const int lives);

  void draw(sf::RenderWindow&);
  void update();

  Direction direction() const { return dir_; }
  void direction(const Direction d) { dir_ = d; }
  const SnakeBody& body() const { return body_; }

  bool isDead() const { return isDead_; }
  void isDead(const bool d) { isDead_ = d; }

  int speed() const { return speed_; }

  void grow();

private:
  SnakeBody body_;
  int segmentSize_;
  sf::RectangleShape bodySegment_;  // shape used in rendering
  Direction dir_;

  int speed_;    // speed of updates
  int lives_;    // hold lives of snake
  bool isDead_;  // check if snake is alive

  void initialize();
  void move();
  void checkHeadCollidesWithBody();
};
