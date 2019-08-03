#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define BELL_POS_X 1150
#define BELL_POS_Y 165
#define BELL_WIDTH 157
#define BELL_HEIGHT 104

#define BELL_ANIM_FRAMES 4
#define BELL_ANIM_REPEATS 2

class Bell : public gm::Button
{
private:
	bool _animate;
	unsigned short _frame;
	unsigned short _repeat;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Bell(sf::Texture *texture);

	void setPosition(float x, float y) { gm::Button::setPosition(x, y); }
	void setPosition(const sf::Vector2f &position) { setPosition(position.x, position.y); }
	void move(float offsetX, float offsetY) { gm::Button::move(offsetX, offsetY); }
	void move(const sf::Vector2f &offset) { move(offset.x, offset.y); }

	void draw(sf::RenderWindow &win);
	bool update_rung(sf::RenderWindow &win);//Returns bool value, so GameState knows if we rang the bell

	const sf::Vector2f getPosition() { return gm::Button::getPosition(); }
};