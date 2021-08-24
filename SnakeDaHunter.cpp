#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing mushroom!");
    window.setPosition(sf::Vector2i(1600, 800));

    window.setTitle("Snake Da Hunter");

    //snake head
    sf::RectangleShape head(sf::Vector2f(20.f, 20.f));
    head.setFillColor(sf::Color(0, 255, 119, 255));
    head.setOrigin(-300, -300);
    sf::Vector2f HeadPosition = head.getPosition();

    //snake body
    sf::RectangleShape body(sf::Vector2f(20.f, 20.f));
    body.setFillColor(sf::Color(0, 181, 84, 255));
    body.setOrigin(-320, -300);
    
    //snake tail
    sf::RectangleShape tail(sf::Vector2f(20.f, 20.f));
    tail.setFillColor(sf::Color(0, 128, 60, 255));
    tail.setOrigin(-340, -300);

    //apple
    srand(time(NULL));
    int Ver = rand() % (800 - 60 + 1) + 0;
    int Hor = rand() % (600 - 60 + 1) + 0;
    sf::CircleShape apple(10.f, 6);
    apple.setFillColor(sf::Color(209, 50, 111, 255));
    //apple.setPosition(Ver.f, Hor.f);
    apple.setOrigin(-Ver, -Hor);

    //apple.setPosition.random;

    //border
    sf::RectangleShape LeftB(sf::Vector2f(30.f, 800.f));
    LeftB.setFillColor(sf::Color(0, 8, 79, 255));
    LeftB.setOrigin(0, 0);

    sf::RectangleShape RightB(sf::Vector2f(30.f, 800.f));
    RightB.setFillColor(sf::Color(0, 8, 79, 255));
    RightB.setOrigin(-770, 0);

    sf::RectangleShape TopB(sf::Vector2f(740.f, 30.f));
    TopB.setFillColor(sf::Color(0, 8, 79, 255));
    TopB.setOrigin(-30, 0);

    sf::RectangleShape BottomB(sf::Vector2f(740.f, 30.f));
    BottomB.setFillColor(sf::Color(0, 8, 79, 255));
    BottomB.setOrigin(-30, -570);



    // event handling loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //if ((mushroomSprite.getPosition().x + txtSize.x / 2 > window.getSize().x &&
        //    increment.x > 0) ||
        //    (mushroomSprite.getPosition().x - txtSize.x / 2 < 0 && increment.x < 0)) {
        //    // reverse the direction on x axis
        //    increment.x = -increment.x;
        //}

        //if ((mushroomSprite.getPosition().y + txtSize.y / 2 > window.getSize().y &&
        //    increment.y > 0) ||
        //    (mushroomSprite.getPosition().y - txtSize.y / 2 < 0 && increment.y < 0)) {
        //    // reverse the direction on y axis
        //    increment.y = -increment.y;
        //}

        //mushroomSprite.setPosition(mushroomSprite.getPosition() + increment);

        window.clear(sf::Color(255, 255, 255, 255));  // white
        window.draw(apple);
        window.draw(head);
        window.draw(body);
        window.draw(tail);
        window.draw(LeftB);
        window.draw(RightB);
        window.draw(TopB);
        window.draw(BottomB);
        window.display();
    }

    return 0;
}