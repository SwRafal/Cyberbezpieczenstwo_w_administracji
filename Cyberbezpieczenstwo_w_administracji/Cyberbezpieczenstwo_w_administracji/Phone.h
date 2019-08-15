#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define PHONE_POS_X 0
#define PHONE_POS_Y 0
#define PHONE_WIDTH 0
#define PHONE_HEIGHT 0

#define MAX_BATTERY_LEVEL 200

class Phone : public gm::Button
{
public:
	Phone(sf::Texture *texture);
	~Phone();





	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	void draw(sf::RenderWindow &win);

};

