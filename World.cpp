#include "world.h"

World::World(const int sz, const sf::Vector2u worldSize)
  : segmentSize_{ sz }
  , worldSize_{ worldSize }
{
  // initialize apple
  apple_.setFillColor(sf::Color::Green);
  apple_.setRadius(segmentSize_ / 2.0);

  initializeWalls();
}

void World::draw(sf::RenderWindow& r)
{
  for ( int i = 0; i < 4; ++i ) {
    r.draw(walls_[i]);
  }
}

void World::initializeWalls()
{
  for ( int i = 0; i < 4; ++i ) {
    walls_[i].setFillColor(sf::Color::Red);
    if ( (i + 1) % 2 == 0 ) {
      walls_[i].setSize(sf::Vector2f(worldSize_.x * segmentSize_, segmentSize_));
    } else {
      walls_[i].setSize(sf::Vector2f(segmentSize_, worldSize_.y * segmentSize_));
    }

    if ( i < 2 ) {
      walls_[i].setPosition(0, 0);
    } else {
      walls_[i].setOrigin(walls_[i].getSize());
      walls_[i].setPosition(sf::Vector2f(worldSize_.x * segmentSize_, worldSize_.y * segmentSize_));
    }
  }
}
