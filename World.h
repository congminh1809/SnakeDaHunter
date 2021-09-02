
#pragma once

#include <SFML/Graphics.hpp>
class Snake;

class World
{
public:
    World(const int, const sf::Vector2u, Snake&);

    void draw(sf::RenderWindow&);
    void update();

private:
    int segmentSize_;
    
    sf::Vector2u worldSize_;
    struct Apple
    {
        sf::Vector2i position;
        sf::CircleShape shape;
    } apple_;
    sf::RectangleShape walls_[4];

    Snake& snake_;
    void initializeApple();
    void initializeWalls();
    void createApple();
};