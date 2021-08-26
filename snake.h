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
  Snake(const int segmentSize);

  void draw(sf::RenderWindow&);
  void update();
  Direction direction() const { return dir_; }
  void direction(const Direction d) { dir_ = d; }

private:
  SnakeBody body_;
  int segmentSize_;
  sf::RectangleShape bodySegment_;  // shape used in rendering
  Direction dir_;

  void move();
};
