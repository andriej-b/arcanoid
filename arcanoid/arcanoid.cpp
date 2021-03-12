// arcanoid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//TODO: paddle bounce ball in different angles
//TODO: add health bar/points. Lost health if ball touch down screen

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Life.h"

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

bool ballFall(ball& Ball, Life& life)
{
    if(Ball.getPosition().y >= (720 - Ball.getBallRadius()-1))
    {
        return true;   
    }
    else {
        return false;
    }
}
int main()
{
    ball ball1(640,370);
    Paddle paddle(640, 700);
    //Life life(1200,5);
    sf::RenderWindow window{ sf::VideoMode{1280,720},"arcanoid" };
    window.setFramerateLimit(60);
    sf::Event event;

    unsigned blocksX{ 17 }, blocksY{ 4 }, blockWidth{ 60 }, blockHeight{ 20 };
    //unsigned lifeWidth{ 40 }, lifeHeight{30};

    int scoreCurrent = 0;
    int lifeCount = 3;

    //my font
    sf::Font myFont;
    if (!myFont.loadFromFile("Minecraft.ttf")) {};

    //player score
    sf::Text score;
    score.setString("SCORE: ");
    score.setFont(myFont);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::Cyan);

    sf::Text currentScore;
    currentScore.setFont(myFont);
    currentScore.setFillColor(sf::Color::Cyan);
    currentScore.setCharacterSize(24);
    currentScore.setPosition(100,0);


    std::vector<Block> blocks;

    for  (int i = 0;  i < blocksY; i++)
    {
        for(int j = 0;j < blocksX; j++)
        {
            blocks.emplace_back((j + 1) * (blockWidth + 10), (i + 2) * (blockHeight + 5), blockWidth, blockHeight);
        }
    }

    std::vector<Life> lifes;

    for(int i = 0; i < lifeCount; i++)
    {
        lifes.emplace_back((1100+(i+1)*50),5);
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
                //calculate score
                scoreCurrent += 5;
                break;
            }
        }
        auto iteratorBlock = std::remove_if(begin(blocks), end(blocks), [](Block& block) {return block.isDestroyed();  });
        blocks.erase(iteratorBlock, end(blocks));

        for(auto& life:lifes)
        {
            if(ballFall(ball1, life))
            {
                life.remove();
                //ball1.bottom();
                break;
            }
        }
        auto iteratorLife = std::remove_if(begin(lifes), end(lifes), [](Life& life) {return life.isRemoved(); });
        lifes.erase(iteratorLife, end(lifes));
        
        

        std::stringstream s;
        s << scoreCurrent;
        currentScore.setString(s.str());

        window.draw(ball1);
        window.draw(paddle);
        window.draw(score);
        window.draw(currentScore);

        for(auto& life: lifes)
        {
            window.draw(life);
        }

        for(auto& block:blocks)
        {
            window.draw(block);
        }

        window.display();
    }

    return 0;
}


