#include "snake.h"

Snake::Snake(const int segmentSize)
  : segmentSize_{ segmentSize }
{
  bodySegment_.setSize(sf::Vector2f(segmentSize_ - 1, segmentSize_ - 1));

  body_.clear();
  body_.emplace_back(5, 7);
  body_.emplace_back(5, 6);
  body_.emplace_back(5, 5);
}

void Snake::draw(sf::RenderWindow& r)
{
  if ( body_.empty() ) return;

  // draw the head
  bodySegment_.setFillColor(sf::Color::Yellow);
  bodySegment_.setPosition(body_[0].position.x * segmentSize_, body_[0].position.y * segmentSize_);
  r.draw(bodySegment_);

  // draw the body
  bodySegment_.setFillColor(sf::Color::Green);
  for ( auto it = body_.begin() + 1; it != body_.end(); ++it ) {
    bodySegment_.setPosition(it->position.x * segmentSize_, it->position.y * segmentSize_);
    r.draw(bodySegment_);
  }
}
