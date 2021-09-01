#pragma once

#include <SFML/Graphics.hpp>

struct SnakeSegment
{
  SnakeSegment(const int x, const int y)
    : position{ x, y }
  {}

  sf::Vector2i position;
};

using SnakeBody = std::vector<SnakeSegment>;

enum class Direction
{
  None,   // no movement
  Up,     // moving up
  Right,  // moving right
  Down,   // moving down
  Left    // moving left
};

class Snake
{
public:

    Snake(const int segmentSize);

    void draw(sf::RenderWindow&);
    void update();

    int lives_();
    bool isDead_();

    //getter/setter
    Direction direction() const { return dir_; }      //getter
    void direction(const Direction d) { dir_ = d; }   //setter
    const SnakeBody& body() const { return body_; }   //getter

    /*int segmentSize() const { return segmentSize_; }
    void segmentSize(int sz) { segmentSize_ = sz; }*/

private:
  SnakeBody body_;
  int segmentSize_;
  sf::RectangleShape bodySegment_;  // shape used in rendering
  Direction dir_;

  //int lives_();
  /*bool isDead();*/
  void initialize();
  void move();
};
