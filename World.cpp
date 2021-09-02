#include "world.h"
#include "snake.h"
#include <iostream>


World::World(const int sz, const sf::Vector2u worldSize, Snake& snake)
    : segmentSize_{ sz }
    , worldSize_{ worldSize }
    , snake_{ snake }

{
    // Initialize random generator
    srand(time(NULL));
    initializeApple();
    initializeWalls();
}

/** Draw the walls and the apple on the render window.
 */
void World::draw(sf::RenderWindow& r)
{
    for (int i = 0; i < 4; ++i) {
        r.draw(walls_[i]);

    }
    r.draw(apple_.shape);

}

/** Update the state of world.
 */
void World::update()
{
    // TODO: implemented as follow
    auto snakePosition = snake_.body().front().position;
    //   - check if the snake can eat the apple
    if (apple_.position == snakePosition)
    {
        createApple();
        /*for (auto it = body_.begin() + 1; it != body_.end(); ++it) {
            body_.emplace_back(it->position.x * segmentSize_, it->position.y * segmentSize_);
        }*/
    }

    //   - check if the snake collides with the walls
    if (snakePosition.x <= 1 || snakePosition.x >= worldSize_.y -1 || snakePosition.x >= worldSize_.y - 1 || snakePosition.y <= 1)
    {
        snake_.isDead(true);
    }
}

void World::initializeApple()
{
    createApple();

    apple_.shape.setFillColor(sf::Color(255, 0, 98, 255));
    apple_.shape.setRadius(segmentSize_ / 2.0);

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
    for (const auto& c : body) {
        if (pos == c.position) return true;
    }
    return false;
}

//int lives_(int live=3) {
//    if (isOnSnake == true)
//    {
//        live--;
//    }
//}

/** Create an apple at a random position in the world. The position must not be on the walls.
 */
void World::createApple()
{
    // DAY 2: Create an apple at a random position in the world. The position must not be on the
    // walls.

      //sf::CircleShape apple_;
      //apple_.setOrigin(Ver, Hor);
    int Ver = rand() % ((worldSize_.x - 2) + 1) + 2;
    int Hor = rand() % ((worldSize_.y - 2) + 1) + 2;

    //Ver = Ver * segmentSize_;
    //Hor = Hor * segmentSize_;

    apple_.position.x = Ver;
    apple_.position.y = Hor;

    apple_.shape.setPosition(Ver * segmentSize_, Hor * segmentSize_);
    std::cout << Ver * segmentSize_ << "   " << Hor * segmentSize_ << std::endl;
}

void World::initializeWalls()
{
    for (int i = 0; i < 4; ++i) {
        walls_[i].setFillColor(sf::Color(255, 0, 98, 255));
        if ((i + 1) % 2 == 0) {
            walls_[i].setSize(sf::Vector2f(worldSize_.x * segmentSize_, segmentSize_));
        }
        else {
            walls_[i].setSize(sf::Vector2f(segmentSize_, worldSize_.y * segmentSize_));
        }

        if (i < 2) {
            walls_[i].setPosition(0, 0);
        }
        else {
            walls_[i].setOrigin(walls_[i].getSize());
            walls_[i].setPosition(sf::Vector2f(worldSize_.x * segmentSize_, worldSize_.y * segmentSize_));
        }
    }
}