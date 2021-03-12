#include "ball.h"

ball::ball(float t_X, float t_Y)
{
	shape.setPosition(t_X, t_Y);
	shape.setRadius(this->ballRadius);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(this->ballRadius, this->ballRadius);
}

float ball::getBallRadius()
{
	return this->shape.getRadius();
}

void ball::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void ball::update()
{
	shape.move(this->velocity);

	if(this->left() < 0)
	{
		velocity.x = ballVelocity;
	}
	else if (this->right() > 1280)
	{
		velocity.x = -ballVelocity;
	}

	if (this->top() < 0)
	{
		velocity.y = ballVelocity;
	}
	else if (this->bottom() > 720)
	{
		//velocity.y = -ballVelocity;
		shape.setPosition(640, 370);
		sf::sleep(sf::milliseconds(1000));
		velocity.x = ballVelocity;
		velocity.y = ballVelocity;
	}
}

float ball::left()
{
	return this->shape.getPosition().x - shape.getRadius();
}
float ball::right()
{
	return this->shape.getPosition().x + shape.getRadius();
}
float ball::top()
{
	return this->shape.getPosition().y - shape.getRadius();
}
float ball::bottom()
{
	return this->shape.getPosition().y + shape.getRadius();
}

void ball::moveDown()
{
	this->velocity.y = ballVelocity;
}
void ball::moveUp()
{
	this->velocity.y = -ballVelocity;
}
void ball::moveRight()
{
	this->velocity.x = ballVelocity;
}
void ball::moveLeft()
{
	this->velocity.x = -ballVelocity;
}

sf::Vector2f ball::getPosition()
{
	return shape.getPosition();
}
