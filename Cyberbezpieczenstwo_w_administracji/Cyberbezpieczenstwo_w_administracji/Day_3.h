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

	const sf::Vector2f PAPERS_POS = sf::Vector2f(860, 510);

	Day_3();
	~Day_3();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};