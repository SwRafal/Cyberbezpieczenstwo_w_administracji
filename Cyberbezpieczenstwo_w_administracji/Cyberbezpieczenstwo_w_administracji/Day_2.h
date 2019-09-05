#pragma once
#include "Day.h"
#include "OfficeFriend.h"
#include "OfficeApplicant.h"


#define THOUGHT_TIME 3000

class Day_2 : public Day
{
public:
	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	int offset;

	int time;

	int state;

	bool init;
	bool initDelay;

	bool coffeeClicked;
	bool bookOpened;

	OfficeApplicant *itGuy;

	OfficeApplicant *boss;

	Day_2();
	~Day_2();

	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};
