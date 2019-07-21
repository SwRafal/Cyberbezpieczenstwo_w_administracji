#pragma once
#include "Engine/Engine.h"
#include "Game.h"

class MenuState : public gm::SlideFrame
{

private:
	gm::gameDataRef data;

public: 
	MenuState(gm::gameDataRef data);
	~MenuState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;

	gm::TextButton playButton;
	gm::TextButton exitButton;

	sf::Sprite background_animation_spritesheet;
	int animationCounteri;
	int animationCounterj;

	sf::Sound clickSound;


};

