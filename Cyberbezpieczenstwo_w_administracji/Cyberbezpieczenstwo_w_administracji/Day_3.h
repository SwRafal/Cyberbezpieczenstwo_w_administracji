#pragma once
#include "Day.h"
#include "textBubble.h"
#include "OfficeApplicant.h"

class Day_3 : public Day
{
public:
	int state;
	bool init;

	bool showButtons;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	OfficeApplicant *ITguy = nullptr;

	//Quests
	bool finish_fought = false;
	bool finish_dialog = false;
	bool finish_boss_dialog = false;
	bool uncover_xero = false;
	bool papers_on_desk = false;
	bool scan_choice = false;
	bool scan_choice_2 = false;
	bool scan_choice_3 = false;

	Day_3();
	~Day_3();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};