#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define SCREEN_SIZE_X 0
#define SCREEN_SIZE_Y 0

#define SMALL_SCREEN_WIDTH 373
#define SMALL_SCREEN_HEIGHT 319

#define PC_POS_X 40
#define PC_POS_Y 200

class pc : public gm::Button
{
	
public:
	pc();
	~pc();

	sf::Sound notification;

	bool powerOn;
	bool showBlackScreen;

	sf::Sprite blackScreen;

	void turnOn();
	void turnOff();

	void update(sf::RenderWindow &win);
	void draw(sf::RenderWindow &win);
};