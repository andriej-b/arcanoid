#pragma once
#include <SFML/Graphics.hpp>
class Paddle : public sf::Drawable
{
public:
	Paddle(float t_X, float t_Y);
	Paddle() = delete;
	~Paddle() = default;

	void update();

	float left();
	float right();
	float top();
	float bottom();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates state)const override;
	sf::RectangleShape shape;
	const float paddleWidth{ 80.0f };
	const float paddleHeight{ 20.0f };
	const float paddleVelocity{ 6.0f };
	sf::Vector2f velocity{ paddleVelocity, 0.f };
};

