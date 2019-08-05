#pragma once

#include "Engine/Engine.h"
#include "Game.h"
#include "Windows.h"

class PauseState : public gm::SlideFrame
{
private:
	gm::gameDataRef data;
public:
	PauseState(gm::gameDataRef data);
	~PauseState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;

	sf::Sprite background;

	sf::RectangleShape rect;

	sf::Sprite buttonsbackground;
	
	float scale;
	int opacity;

	bool resuming;

	gm::TextButton resumeButton;
	gm::TextButton saveButton;
	gm::TextButton menuButton;

	sf::Sound clickSound;

};

