#pragma once
#include "Engine/Engine.h"

#define FULL_CLOSED_EYES 3

class Eyelids
{
private:
	unsigned short closed_eyes_lvl;
	sf::RectangleShape *eyelids = nullptr;
	unsigned short up_eyelid_height;
	unsigned short down_eyelid_height;
	unsigned short up_eyelid_destination;
	unsigned short down_eyelid_destination;

	void adjust();
public:
	Eyelids();
	~Eyelids();

	void open();
	void close();
	void decreaseLvl();
	void increaseLvl();
	void setLvl(unsigned short lvl);

	void update();
	void draw(sf::RenderWindow &win);

	unsigned short getLvl() { return closed_eyes_lvl; }
};