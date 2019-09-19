#pragma once
#include "Day.h"
#include "textBubble.h"
#include "OfficeApplicant.h"

class Day_4 : public Day
{
public:
	int state;
	int offset;
	bool showButtons;

	//day start
	bool coffeeClicked = false;
	bool bookOpened = false;

	//quest 1
	bool showNewspaper;
	sf::Sprite newspaper;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	OfficeApplicant *itGuy = nullptr;
	OfficeApplicant *boss = nullptr;

	Day_4();
	~Day_4();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};