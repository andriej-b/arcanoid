#pragma once
#include <SFML/Graphics.hpp>

class ball : public sf::Drawable
{
public:
	ball(float t_X, float t_Y);
	ball() = delete;
	~ball() = default;
	void update();
	
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();

	sf::Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();
private:
	sf::CircleShape shape;
	const float ballRadius{10.0f};
	const float ballVelocity{3.0f};
	sf::Vector2f velocity{ ballVelocity,ballVelocity };
	void draw(sf::RenderTarget& target, sf::RenderStates state)const override;
};

