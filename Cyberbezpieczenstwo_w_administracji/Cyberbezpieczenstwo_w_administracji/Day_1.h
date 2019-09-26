#pragma once
#include "Day.h"
#include "textBubble.h"
#include "OfficeApplicant.h"

#define THOUGHT_TIME 3000


class Day_1 : public Day
{
public:
	int state;
	bool init;

	bool showButtons;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	OfficeApplicant *ITguy = nullptr;

	bool talked = false;
	bool talked2 = false;

	Day_1();
	~Day_1();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};