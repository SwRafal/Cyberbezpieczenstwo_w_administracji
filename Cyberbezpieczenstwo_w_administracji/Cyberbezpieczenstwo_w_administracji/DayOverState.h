#pragma once
#include "Game.h"
#include "Engine/Engine.h"

class DayOverState : public gm::SlideFrame
{
private:
	gm::gameDataRef data;
public:
	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;

	sf::Font arial;
	sf::Text text;

	gm::Button next;
	gm::Information knowledge;

	sf::Sprite background;

	short text_alpha;

	int state;

	DayOverState(gm::gameDataRef data);
	~DayOverState();
};

