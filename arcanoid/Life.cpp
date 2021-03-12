#include "Life.h"

Life::Life(float t_X, float t_Y)
{
	shape.setPosition(t_X, t_Y);

	shape.setPointCount(6);
	shape.setPoint(0, sf::Vector2f(10, 0));
	shape.setPoint(1, sf::Vector2f(20, 10));
	shape.setPoint(2, sf::Vector2f(30, 0));
	shape.setPoint(3, sf::Vector2f(40, 10));
	shape.setPoint(4, sf::Vector2f(20, 30));
	shape.setPoint(5, sf::Vector2f(0, 10));

	shape.setFillColor(sf::Color::Red);
}
void Life::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->shape, state);
}
bool Life::isRemoved()
{
	return this->removed;
}
void Life::remove()
{
	this->removed = true;
}