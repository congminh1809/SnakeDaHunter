#include "game.h"

const int SEGMENT_SIZE{ 20 };

const std::string WINDOW_TITLE{ "Yet Another Snake Game" };

const int SEGMENTS_X{ 40 };
const int SEGMENTS_Y{ 30 };

Game::Game()
  : segmentSize_{ SEGMENT_SIZE }
  , snake_(segmentSize_)
  , world_(segmentSize_, sf::Vector2u{ SEGMENTS_X, SEGMENTS_Y })
  , isDone_{ false }
{
  renderWindow_.create(sf::VideoMode{ SEGMENTS_X * SEGMENT_SIZE, SEGMENTS_Y * SEGMENT_SIZE },
                       WINDOW_TITLE,
                       sf::Style::Default);
}

void Game::update()
{
  sf::Event event;
  while ( renderWindow_.pollEvent(event) ) {
    if ( event.type == sf::Event::Closed ) { isDone_ = true; }
  }
}

void Game::draw()
{
  renderWindow_.clear(sf::Color::Black);

  snake_.draw(renderWindow_);
  world_.draw(renderWindow_);

  renderWindow_.display();
}
