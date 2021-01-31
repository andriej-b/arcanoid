#include "Paddle.h"

Paddle::Paddle(float t_X, float t_Y)
{
	shape.setPosition(t_X, t_Y);
	shape.setSize(sf::Vector2f{ this->paddleWidth, this->paddleHeight });
	shape.setFillColor(sf::Color::Blue);
	shape.setOrigin(this->paddleWidth/2.f, this->paddleHeight/2.f);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}

void Paddle::update()
{
	this->shape.move(this->velocity);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && this->left() > 0)
	{
		velocity.x = -paddleVelocity;
	}else
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && this->right() > 0)
	{
		velocity.x = paddleVelocity;
	}else
	{
		velocity.x = 0;
	}
}

float Paddle::left()
{
	return this->shape.getPosition().x - shape.getSize().x / 2.f;
}
float Paddle::right()
{
	return this->shape.getPosition().x + shape.getSize().x / 2.f;
}
float Paddle::top()
{
	return this->shape.getPosition().y - shape.getSize().y / 2.f;
}
float Paddle::bottom()
{
	return this->shape.getPosition().y + shape.getSize().y / 2.f;
}