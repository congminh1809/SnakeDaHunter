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

class Snake
{
public:
  Snake(const int segmentSize);

  void draw(sf::RenderWindow&);

private:
  SnakeBody body_;
  int segmentSize_;
  sf::RectangleShape bodySegment_;  // shape used in rendering
};
