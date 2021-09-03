#include "snake.h"
#include <iostream>

Snake::Snake(const int segmentSize, const int lives)
  : segmentSize_{ segmentSize }
  , lives_{ lives }
  , isDead_{ false }
{
  bodySegment_.setSize(sf::Vector2f(segmentSize_ - 1, segmentSize_ - 1));
  initialize();
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

/** Update the state of the snake.
 */
void Snake::update()
{
  if ( body_.empty() || dir_ == Direction::None ) return;

  move();

  checkHeadCollidesWithBody();
}

/** Extend the snake's body by one segment
 */
void Snake::grow() {
  
}

void Snake::initialize()
{
	body_.clear();
	body_.emplace_back(5, 14);
	body_.emplace_back(5, 13);
	body_.emplace_back(5, 12);
	body_.emplace_back(5, 11);
	body_.emplace_back(5, 10);
	body_.emplace_back(5, 9);
	body_.emplace_back(5, 8);
	body_.emplace_back(5, 7);
	body_.emplace_back(5, 6);
	body_.emplace_back(5, 5);

  dir_ = Direction::None;
}

/** Move the snake to the current direction.
 */
void Snake::move()
{
  // DAY 2: Write code to change the positions of snake body's segment following the current
  // value of dir_
  for ( std::size_t i = body_.size() - 1; i > 0; --i ) {
    body_[i].position = body_[i - 1].position;
  }
  if ( dir_ == Direction::Up ) {
    --body_[0].position.y;
  } else if ( dir_ == Direction::Right ) {
    ++body_[0].position.x;
  } else if ( dir_ == Direction::Down ) {
    ++body_[0].position.y;
  } else if ( dir_ == Direction::Left ) {
    --body_[0].position.x;
  }
}

/** Check if the head collides with its body.
 *
 * If the head collides with its body then cut the body from the touch point to the end and
 * decrease the lives by one. And if the lives is 0 then set isDead_ to true.
 */
void Snake::checkHeadCollidesWithBody()
{
  if ( body_.size() < 6 ) return;

  for ( auto it = body_.begin() + 1; it != body_.end(); ++it ) {
    if ( body_[0].position == it->position ) {
      --lives_;
      std::cout << "LIVES:" << lives_ << std::endl;
      // TODO: cut the body from the touch point to the end
      break;
    }
  }
  if ( lives_ == 0 ) isDead_ = true;

  // another way to implement using std::find_if
  // auto it = std::find_if(body_.begin() + 1, body_.end(), [&](const SnakeSegment& c) {
  //   return body_[0].position == c.position;
  // });

  // if ( it != body_.end() ) {
  //   if ( --lives_ == 0 ) isDead_ = true;
  // }
}
