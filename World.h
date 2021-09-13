#pragma once

#include <SFML/Graphics.hpp>

class Snake;

class World
{
public:
  World(const int, const sf::Vector2u, Snake&);

  void draw(sf::RenderWindow&);
  void update();
  int numberOfApplesCreated();

private:
  int segmentSize_;
  long int score = 0;
  sf::Vector2i worldSize_;
  Snake& snake_;
  struct Apple
  {
    sf::Vector2i position;
    sf::CircleShape shape;
  } apple_;
  sf::RectangleShape walls_[4];
  int nApplesCreated_;  // hold the number of apples created so far

  void initializeApple();
  void initializeWalls();
  void createApple();
};
