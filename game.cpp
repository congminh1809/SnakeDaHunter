#include "game.h"
#include <iomanip>
#include <iostream>
#include <sstream>

const int SEGMENT_SIZE{ 20 };
const int SEGMENTS_X{ 40 };
const int SEGMENTS_Y{ 30 };
const int SNAKE_LIVES{ 3 };
const int SNAKE_SPEED{ 20 };

const std::string WINDOW_TITLE{ "Yet Another Snake Game" };
const int MAX_FPS{ 120 };

/** Constructor: create world, snake and a render window.
 */
Game::Game()
  : segmentSize_{ SEGMENT_SIZE }
  , snake_(segmentSize_, SNAKE_LIVES, SNAKE_SPEED)
  , world_(segmentSize_, sf::Vector2u{ SEGMENTS_X, SEGMENTS_Y }, snake_)
  , isDone_{ false }
{
  renderWindow_.create(sf::VideoMode{ SEGMENTS_X * SEGMENT_SIZE, SEGMENTS_Y * SEGMENT_SIZE },
                       WINDOW_TITLE,
                       sf::Style::Titlebar | sf::Style::Close);

  // Try to reduce CPU load in each running loop by setting framerate limit.
  // After each sf::RenderWindow::display() call, the program will sleep a bit
  // to ensure the current frame last long enough to match the framerate limit.
  renderWindow_.setFramerateLimit(MAX_FPS);

  elapsedTime_ = 0;

  initializeStatusBar();
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
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake_.direction() != Direction::Down ) {
    snake_.direction(Direction::Up);
  } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
              snake_.direction() != Direction::Left ) {
    snake_.direction(Direction::Right);
  } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
              snake_.direction() != Direction::Up ) {
    snake_.direction(Direction::Down);
  } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
              snake_.direction() != Direction::Right ) {
    snake_.direction(Direction::Left);
  }

  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) isDone_ = true;
}

/** Update the states of game after checking events and input
 */
void Game::update()
{
  float timeOfUpdate = 1.0 / snake_.speed();

  if ( elapsedTime_ > timeOfUpdate ) {
    snake_.update();
    world_.update();

    updateStatusBar();

    if ( snake_.isDead() ) {
      isDone_ = true;
      std::cout << "GAME OVER!\n";
    }

    elapsedTime_ -= timeOfUpdate;
  }
}

void Game::draw()
{
  renderWindow_.clear(sf::Color::Black);

  snake_.draw(renderWindow_);
  world_.draw(renderWindow_);

  renderWindow_.draw(statusBar_);

  renderWindow_.display();
}

void Game::restartClock()
{
  elapsedTime_ += clock_.restart().asSeconds();
}

void Game::initializeStatusBar()
{
  font_.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
  statusBar_.setFont(font_);
  statusBar_.setCharacterSize(segmentSize_ - 4);
  statusBar_.setFillColor(sf::Color(0, 255, 170, 255));
  statusBar_.setPosition(segmentSize_ + 2, (SEGMENTS_Y - 1) * SEGMENT_SIZE - 1);
  statusBar_.setStyle(sf::Text::Bold);
}

void Game::updateStatusBar()
{
  std::ostringstream oss;
  /*score += snake_.body().size() * (world_.numberOfApplesCreated() - 1);*/
  oss << "Lives: " << snake_.lives() << "  Body: " << std::setw(3) << snake_.body().size()
      << "  Speed: " << std::setw(2) << snake_.speed() << "  Score: " << std::setw(3)
      << world_.score() << "           Pause [SPACE]  Main Menu [ESC]";
  statusBar_.setString(oss.str().c_str());
  
}
