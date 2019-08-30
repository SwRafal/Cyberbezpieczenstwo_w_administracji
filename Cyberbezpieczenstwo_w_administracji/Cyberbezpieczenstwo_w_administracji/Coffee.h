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

	void setLevel(unsigned short level=MAX_COFFEE_LEVEL);

	unsigned short getLevel() { return _level; }

	void reset();
};

