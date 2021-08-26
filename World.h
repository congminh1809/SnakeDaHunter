#pragma once

#include <SFML/Graphics.hpp>

class World
{
public:
  World(const int, const sf::Vector2u);

  void draw(sf::RenderWindow&);
  void update();
  int Ver = rand() % (800 - 60 + 1) + 0;
  int Hor = rand() % (600 - 60 + 1) + 0;

private:
  int segmentSize_;
  sf::Vector2u worldSize_;
  struct Apple
  {
    sf::Vector2i position;
    sf::CircleShape shape;
  } apple_;
  sf::RectangleShape walls_[4];

  void initializeApple();
  void initializeWalls();
  void createApple();
};
