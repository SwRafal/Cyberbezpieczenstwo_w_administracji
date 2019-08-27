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

	int time;

	sf::RectangleShape background;

	sf::Sprite screen;
	sf::Sprite table;

	Day_0();
	void update(GameState* gs, sf::RenderWindow &win) override;
	void draw(GameState* gs);
	
	
};