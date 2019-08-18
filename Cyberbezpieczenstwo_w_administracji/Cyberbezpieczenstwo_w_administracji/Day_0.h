#pragma once
#include "Day.h"


class Day_0 : public Day
{
public:


	int state;
	bool showTextField;
	bool showButtons;
	bool part1Over;
	bool reset;
	bool init;

	sf::RectangleShape background;

	Day_0();
	void update(GameState* gs) override;
	void draw(GameState* gs);
	
	
};