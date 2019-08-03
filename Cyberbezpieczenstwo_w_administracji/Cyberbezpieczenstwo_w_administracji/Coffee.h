#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define COFFEE_POS_X 385
#define COFFEE_POS_Y 450
#define COFFEE_WIDTH 137
#define COFFEE_HEIGHT 165

#define MAX_COFFEE_LEVEL 39

/*DETAILS (position...)*/

class Coffee : public gm::Button
{
private:
	unsigned short _level;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Coffee(sf::Texture *texture);

	void draw(sf::RenderWindow &win);
	bool update_drunk(sf::RenderWindow &win);//Returns bool value, so baterry object can know if it should be charged in GameState

	void setPosition(float x, float y) { gm::Button::setPosition(x, y); }
	void setPosition(const sf::Vector2f &position) { setPosition(position.x,position.y); }
	void move(float offsetX, float offsetY) { gm::Button::move(offsetX, offsetY); }
	void move(const sf::Vector2f &offset) { move(offset.x,offset.y); }

	void setLevel(unsigned short level=MAX_COFFEE_LEVEL);

	const sf::Vector2f getPosition() { return gm::Button::getPosition(); }

	unsigned short getLevel() { return _level; }
};

