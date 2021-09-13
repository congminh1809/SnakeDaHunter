#include "world.h"
#include "snake.h"
#include <iostream>

/** Construct a world containing walls and an apple.
 *
 * The world is a grid of segments and has 4 walls on the boundary and an apple
 * generated at a random position. It also gets a reference to a snake so it can
 * check the snake's position with the walls and the apple.
 */
World::World(const int sz, const sf::Vector2u worldSize, Snake& snake)
  : segmentSize_{ sz }
  , worldSize_{ worldSize }
  , snake_{ snake }
  , nApplesCreated_{ 0 }
{
  // Initialize random generator
  srand(time(nullptr));

  initializeApple();
  initializeWalls();
}

/** Draw the walls and the apple on the render window.
 */
void World::draw(sf::RenderWindow& r)
{
  for ( int i = 0; i < 4; ++i ) {
    r.draw(walls_[i]);
  }
  r.draw(apple_.shape);
}

/** Update the state of world.
 */
void World::update()
{
  // DAY 3: implemented as follow
  auto snakePosition = snake_.body().front().position;
  //   - check if the snake can eat the apple
  if ( snakePosition == apple_.position ) {
    // extend the snake's body by 1 segment
    snake_.grow();
    score_ += snake_.body().size() * (nApplesCreated_);
    //std::cout << "SCORE:   " << score << std::endl;

    // create another apple
    createApple();

    // Increase snake's speed by 1 after eating every 10 apples
    if ( nApplesCreated_ % 10 == 1 ) { snake_.speed(snake_.speed() + 1); }
  }

  //   - check if the snake collides with the walls
  if ( snakePosition.x <= 0 || snakePosition.x >= worldSize_.x - 1 || snakePosition.y <= 0 ||
       snakePosition.y >= worldSize_.y - 1 ) {
    snake_.isDead(true);
  }
}

void World::initializeApple()
{
  apple_.shape.setFillColor(sf::Color(255, 0, 98, 255));
  apple_.shape.setRadius(segmentSize_ / 2.0);

  createApple();
}

/** Check if a position is occupied by the snake body.
 *
 * @param 'pos' The position to be checked.
 * @param 'body' Body of the snake.
 *
 * @return true if the position is occupied by the snake body.
 *         Otherwise, returns false.
 */
static bool isOnSnake(const sf::Vector2i& pos, const SnakeBody& body)
{
  for ( const auto& c : body ) {
    if ( pos == c.position ) return true;
  }
  return false;
}

/** Create an apple at a random position in the world.
 */
void World::createApple()
{
  // DAY 2: Create an apple at a random position in the world.

  // The position must not be on the walls.
  sf::Vector2i pos{ rand() % (worldSize_.x - 2) + 1, rand() % (worldSize_.y - 2) + 1 };

  // and it must not be on the snake body :)
  while ( isOnSnake(pos, snake_.body()) ) {
    pos = { rand() % (worldSize_.x - 2) + 1, rand() % (worldSize_.y - 2) + 1 };
  }

  apple_.shape.setPosition(pos.x * segmentSize_, pos.y * segmentSize_);
  apple_.position = pos;
  std::cout << "Horizontal: " << pos.x * segmentSize_ << "    " << "Vertical: " << pos.y * segmentSize_ << std::endl;

  ++nApplesCreated_;
}

void World::initializeWalls()
{
  for ( int i = 0; i < 4; ++i ) {
    walls_[i].setFillColor(sf::Color(255, 0, 98, 255));
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

int World::score()
{
    
    return score_; 
}
