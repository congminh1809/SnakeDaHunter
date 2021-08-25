#pragma once

#include <SFML/Graphics.hpp>

class World
{
public:
  World(const int, const sf::Vector2u);

  void draw(sf::RenderWindow&);

private:
  int segmentSize_;
  sf::Vector2u worldSize_;
  sf::CircleShape apple_;
  sf::RectangleShape walls_[4];

  void initializeWalls();
};
