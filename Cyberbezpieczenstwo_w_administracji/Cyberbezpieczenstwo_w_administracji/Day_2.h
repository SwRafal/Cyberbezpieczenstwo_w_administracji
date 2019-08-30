#pragma once
#include "Day.h"
#include "OfficeFriend.h"


class Day_2 : public Day
{
public:
	

	int time;

	int state;

	bool init;

	OfficeFriend *itGuy;

	Day_2();
	~Day_2();

	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};
