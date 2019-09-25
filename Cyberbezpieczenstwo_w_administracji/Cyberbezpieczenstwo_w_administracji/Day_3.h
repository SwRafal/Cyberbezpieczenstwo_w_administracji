#pragma once
#include "Day.h"
#include "textBubble.h"
#include "OfficeApplicant.h"
#include "Phishing.h"

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

	sf::Sprite *lighting = nullptr;

	//Phishing
	Phishing minigame;

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

	//BURZA SPALI£A JE¿ELI ANIELA

	const sf::Vector2f PAPERS_POS = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 120);

	Day_3();
	~Day_3();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};