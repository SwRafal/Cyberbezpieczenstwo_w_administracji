#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define STAMP_WIDTH 109
#define STAMP_HEIGHT 141

#define DESK_BEGIN 490 //The height level (from top) desk starts at

class Stamp : protected gm::Button
{
	bool _active;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Stamp(sf::Texture *texture);
	~Stamp();

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);

	void setPosition(float x, float y) { gm::Button::setPosition(x, y); }
	void setPosition(const sf::Vector2f &position) { setPosition(position.x, position.y); }
	void move(float offsetX, float offsetY) { gm::Button::move(offsetX, offsetY); }
	void move(const sf::Vector2f &offset) { move(offset.x, offset.y); }

	void setActiveFlag(bool state);
	void setActive();
	void setInactive();
	void switchActivation();/*Negate the 'active' flag*/

	const sf::Vector2f getPosition() { return gm::Button::getPosition(); }

	bool isActive() { return _active; }
};

