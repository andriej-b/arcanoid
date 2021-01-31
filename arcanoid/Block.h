#pragma once
#include <SFML/Graphics.hpp>
class Block : public sf::Drawable
{
public:
	Block(float t_X, float t_Y, float t_Width, float t_Height);
	Block() = delete;
	~Block() = default;

	void update();
	sf::Vector2f getPosition();

	float left();
	float right();
	float top();
	float bottom();

	bool isDestroyed();
	void destroy();
	sf::Vector2f getSize();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	sf::RectangleShape shape;
	bool destroyed{ false };
};

