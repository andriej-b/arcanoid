#pragma once
#include<SFML/Graphics.hpp>

class Life : public sf::Drawable
{
public:
	Life(float t_X, float t_Y);
	Life() = delete;
	~Life() = default;

	bool isRemoved();
	void remove();

private:
	sf::ConvexShape shape;

	void draw(sf::RenderTarget& target, sf::RenderStates state)const override;
	bool removed{ false };
};

