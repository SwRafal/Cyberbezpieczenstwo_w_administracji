#pragma once
#include "Engine/Engine.h"
#include "Game.h"

class SplashScreenState : public gm::SlideFrame
{

private:
	gm::gameDataRef data;

public: 
	SplashScreenState(gm::gameDataRef data);
	~SplashScreenState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;

};

