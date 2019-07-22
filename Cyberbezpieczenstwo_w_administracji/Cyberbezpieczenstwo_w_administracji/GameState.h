#pragma once
#include "Engine/Engine.h"
#include "Game.h"
#include "Functions.h"

void error_win_close();

class GameState : public gm::SlideFrame
{
private:
	gm::gameDataRef data;

	/*Settings*/
	unsigned int day;

	/*Environment*/
	sf::Sprite wall;
	//sf::Sprite calendrar;
	sf::Sprite drawer;
	sf::Sprite customer_window;
	sf::Sprite desk;
	//sf::Sprite computer;
	//sf::Sprite monitor;
	sf::Sprite keyboard;
	//sf::Sprite telephone;
	sf::Sprite watch;

public:
	GameState(gm::gameDataRef data);
	~GameState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;
};