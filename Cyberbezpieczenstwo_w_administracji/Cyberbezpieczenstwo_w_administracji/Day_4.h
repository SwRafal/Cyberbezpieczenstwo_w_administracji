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
	bool callIn;
	bool drawDowod;

	//day start
	bool coffeeClicked = false;
	bool bookOpened = false;

	//quest 1
	bool showNewspaper;
	sf::Sprite newspaper;
	sf::Sprite dowod1;
	bool quest1completed = false;

	//quest 2
	bool quest2completed = false;

	//petenci
	OfficeApplicant * petent1;
	OfficeApplicant * petent2;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	OfficeApplicant *itGuy = nullptr;
	OfficeApplicant *boss = nullptr;

	Day_4();
	~Day_4();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};