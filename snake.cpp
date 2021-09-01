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

/** Update the state of the snake.
 */
void Snake::update()
{
  if ( body_.empty() || dir_ == Direction::None ) return;

  move();
}

//Count how many times the snake's head touch snake's body
int Snake::lives_() {
	int live = 3;
	for (auto it = body_.begin() + 1; it != body_.end(); ++it) {
		if (body_[0].position.x / segmentSize_ == it->position.x / segmentSize_ && 
			body_[0].position.y / segmentSize_ == it->position.y / segmentSize_)
		{
			live--;
		}
	}
	return live;
}

bool Snake::isDead_() {

}

void Snake::initialize() {

	body_.clear();
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
	for (std::size_t i = body_.size() - 1; i > 0; --i)
	{
		body_[i].position = body_[i - 1].position;
	}
	if (dir_ == Direction::Up)
	{
		--body_[0].position.y;
	}
	else if (dir_ == Direction::Right)
	{
		++body_[0].position.x;
	}
	else if (dir_ == Direction::Down)
	{
		++body_[0].position.y;
	}
	else if (dir_ == Direction::Left)
	{
		--body_[0].position.x;
	}
}
