
#pragma once

#include <SFML/Graphics.hpp>

class World
{
public:
    World(const int, const sf::Vector2u);

    void draw(sf::RenderWindow&);
    void update();

private:
    int segmentSize_;
    int lives_();
    bool isDead();
    sf::Vector2u worldSize_;
    struct Apple
    {
        sf::Vector2i position;
        sf::CircleShape shape;
    } apple_;
    sf::RectangleShape walls_[4];

    void initializeApple();
    void initializeWalls();
    void createApple();
};