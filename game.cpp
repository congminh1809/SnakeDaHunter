#include "game.h"

const int SEGMENT_SIZE{ 20 };

const std::string WINDOW_TITLE{ "Yet Another Snake Game" };

const int SEGMENTS_X{ 40 };
const int SEGMENTS_Y{ 30 };

/** Constructor: create world, snake and a render window.
 */
Game::Game()
  : segmentSize_{ SEGMENT_SIZE }
  , world_(segmentSize_, sf::Vector2u{ SEGMENTS_X, SEGMENTS_Y })
  , snake_(segmentSize_)
  , isDone_{ false }
{
  renderWindow_.create(sf::VideoMode{ SEGMENTS_X * SEGMENT_SIZE, SEGMENTS_Y * SEGMENT_SIZE },
                       WINDOW_TITLE,
                       sf::Style::Default);
  renderWindow_.setFramerateLimit(60);
}

/** Destructor: close the render window
 */
Game::~Game()
{
  renderWindow_.close();
}

/** Check and handle event queue
 */
void Game::checkEvents()
{
  sf::Event event;
  // while there are pending events
  while ( renderWindow_.pollEvent(event) ) {
    if ( event.type == sf::Event::Closed ) { isDone_ = true; }
  }
}

/** Check and handle real-time input events
 */
void Game::checkInput()
{
  // DAY 2: Write code to check if key Up, Right, Down, or Left is pressed
  // If yes then set the direction of the snake by using Snake::direction(Direction)
  // Remember to check if we can set the new direction. For example, if the current direction is
  // Left then we cannot set the new direction to Right because the head will go back to the body.
	//Direction dir_;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake_.direction() != Direction::Down)
		snake_.direction(Direction::Up);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake_.direction() != Direction::Up)
		snake_.direction(Direction::Down);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake_.direction() != Direction::Right)
		snake_.direction(Direction::Left);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake_.direction() != Direction::Left)
		snake_.direction(Direction::Right);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
		isDone_ = true;
	
}

/** Update the states of game after checking events and input
 */
void Game::update()
{
  snake_.update();
  world_.update();
}

void Game::draw()
{
  renderWindow_.clear(sf::Color::Black);

  snake_.draw(renderWindow_);
  world_.draw(renderWindow_);

  renderWindow_.display();
}
