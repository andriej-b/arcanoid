// arcanoid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "ball.h"
#include "Paddle.h"
#include "Block.h"

template<class T1, class T2> bool isIntersecting(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right()
        && A.bottom() >= B.top() && A.top() <= B.bottom();
}

bool collisionTest(Paddle& paddle, ball& ball)
{
    if (!isIntersecting(paddle, ball)) return false;

    ball.moveUp();

    if(ball.getPosition().x < paddle.getPosition().x)
    {
        ball.moveLeft();
    }else
    if (ball.getPosition().x > paddle.getPosition().x)
    {
        ball.moveRight();
    }


}

bool collisionTest(Block& block, ball& Ball)
{
    if (!isIntersecting(block, Ball)) return false;

    block.destroy();

    float overlapLeft{ Ball.right() - block.left() };
    float overlapRight{ block.right() - Ball.left() };

    float overlapTop{ Ball.bottom() - block.top() };
    float overlapBottom{ block.bottom() - Ball.top() };

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    if(abs(minOverlapX) < abs(minOverlapX))
    {
        ballFromLeft ? Ball.moveLeft() : Ball.moveRight();
    }
    else
    {
        ballFromTop ? Ball.moveUp() : Ball.moveDown();
    }
}

int main()
{
    ball ball1(640,370);
    Paddle paddle(640, 700);
    sf::RenderWindow window{ sf::VideoMode{1280,720},"arcanoid" };
    window.setFramerateLimit(60);
    sf::Event event;
    unsigned blocksX{ 17 }, blocksY{ 4 }, blockWidth{ 60 }, blockHeight{ 20 };

    std::vector<Block> blocks;

    for  (int i = 0;  i < blocksY; i++)
    {
        for(int j = 0;j < blocksX; j++)
        {
            blocks.emplace_back((j + 1) * (blockWidth + 10), (i + 2) * (blockHeight + 5), blockWidth, blockHeight);
        }
    }

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

        collisionTest(paddle, ball1);
        for(auto& block:blocks)
        {
            if (collisionTest(block, ball1)) 
            {
                break;
            }
        }
        auto iterator = std::remove_if(begin(blocks), end(blocks), [](Block& block) {return block.isDestroyed();  });
        blocks.erase(iterator, end(blocks));

        window.draw(ball1);
        window.draw(paddle);

        for(auto& block:blocks)
        {
            window.draw(block);
        }

        window.display();
    }

    return 0;
}


