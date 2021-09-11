#include "world.h"
#include "snake.h"
#include <iostream>

using namespace sf;

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
{
  // Initialize random generator
  srand(time(nullptr));

  initializeApple();
  initializeWalls();
  setUpText();
}

/** Draw the walls and the apple on the render window.
 */
void World::draw(sf::RenderWindow& r)
{
  for ( int i = 0; i < 4; ++i ) {
    r.draw(walls_[i]);
  }
  r.draw(apple_.shape);
  r.draw(text_);
  r.draw(score_);

}

/** Update the state of world.
 */
void World::update()
{
  // DAY 3: implemented as follow
  auto snakePosition = snake_.body().front().position;
  //   - check if the snake can eat the apple
  if ( snakePosition == apple_.position ) {
    // TODO: extend the snake's body by 1
    snake_.grow();
    score++;

    //Print score
    std::string scoreString = std::to_string(score);
    font_.loadFromFile("C:/Windows/Fonts/arial.ttf");
    score_.setFont(font_);
    score_.setString(scoreString);
    score_.setCharacterSize(16);
    score_.setFillColor(sf::Color(0, 179, 255, 255));
    score_.setStyle(sf::Text::Bold);
    score_.setPosition(220, 0);
    //std::cout << "Score: " << score << std::endl;

    // create another apple
    createApple();
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

void World::setUpText() {
    font_.loadFromFile("C:/Windows/Fonts/arial.ttf");
    text_.setFont(font_);
    text_.setString("Snake Da Hunter     Score:      Live:      Length: ");
    text_.setCharacterSize(16);
    text_.setFillColor(sf::Color(0, 179, 255, 255));
    text_.setStyle(sf::Text::Bold);
    text_.setPosition(0, 0);

}


