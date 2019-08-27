#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define SCREEN_SIZE_X 0
#define SCREEN_SIZE_Y 0

class pc : public gm::Button
{
	
public:
	pc();
	~pc();

	bool powerOn;

	sf::Sprite screen;

	void update(sf::RenderWindow &win);
};