#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include "Rubbish.h"

#define BIN_POS_X 945
#define BIN_POS_Y 630
#define BIN_WIDTH 190
#define BIN_HEIGHT 295

/*DETAILS (position...)*/

class Bin : public gm::Button
{
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Bin(sf::Texture *texture);

	void draw(sf::RenderWindow &win);
};

