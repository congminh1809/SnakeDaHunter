#pragma once

#include <SFML/Graphics.hpp>

class Snake;

class World
{
public:
  World(const int, const sf::Vector2u, Snake&);

  void draw(sf::RenderWindow&);
  void update();
  int score = 0;

private:
  int segmentSize_;
  sf::Vector2i worldSize_;
  sf::Text text_;
  sf::Text score_;
  sf::Text live_;
  sf::Font font_;

  struct Apple
  {
    sf::Vector2i position;
    sf::CircleShape shape;
  } apple_;
  sf::RectangleShape walls_[4];
  
  Snake& snake_;

  void initializeApple();
  void initializeWalls();
  void createApple();
  void setUpText();
};
