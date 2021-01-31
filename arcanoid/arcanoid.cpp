// arcanoid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "ball.h"

int main()
{
    ball ball1(600,370);
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
        window.draw(ball1);

        window.display();
    }

    return 0;
}


