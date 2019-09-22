#pragma once
#include "Day.h"
#include "textBubble.h"
#include "OfficeApplicant.h"

class Day_3 : public Day
{
private:
	const float offset = 10;

public:
	int state;
	bool init;

	bool showButtons;

	textBubble *ringIT = nullptr;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	OfficeApplicant *ITguy = nullptr;
	OfficeApplicant *boss = nullptr;

	sf::Sprite *peach = nullptr;
	sf::Int32 scan_time;
	sf::Sound beep;

	//Quest2
	bool test_scan = false;
	bool test_scan_2 = false;
	bool test_scan_3 = false;
	bool scan_papers = false;
	bool finished_scans = false;
	bool finish_communique = false;
	bool broken_scanner = false;
	bool fix_scanner = false;
	bool finish_thought_2 = false;
	bool finish_boss_dialog_2 = false;
	bool things_vanish = false;

	//Phone
	bool phone_pickup = false;
	bool finish_phone = false;
	bool finish_IT_dialog = false;

	//Mobile
	bool mobile_pickup = false;
	bool aniela_talking = false;
	bool passed_time = false;

	//Quest3
	bool finish_boss_dialog_3 = false;

	//BURZA SPALI�A JE�ELI ANIELA

	const sf::Vector2f PAPERS_POS = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 120);

	Day_3();
	~Day_3();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};