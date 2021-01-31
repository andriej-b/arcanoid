// arcanoid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "ball.h"
#include "Paddle.h"

int main()
{
    ball ball1(640,370);
    Paddle paddle(640, 700);
    sf::RenderWindow window{ sf::VideoMode{1280,720},"arcanoid" };
    window.setFramerateLimit(60);
    sf::Event event;

    while(true)
    {
        window.clear(sf::Color::Black);
        window.pollEvent(event);

        if(event.type == sf::Event::Closed)
        {
            window.close();
            break;
        }
        ball1.update();
        paddle.update();

        window.draw(ball1);
        window.draw(paddle);

        window.display();
    }

    return 0;
}


