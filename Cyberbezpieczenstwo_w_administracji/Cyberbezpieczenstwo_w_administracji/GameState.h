#pragma once
#include "Engine/Engine.h"
#include "Game.h"

class GameState : public gm::SlideFrame
{
private:
	gm::gameDataRef data;

	sf::Sprite wall;
	//sf::Sprite calendrar;
	sf::Sprite drawer;
	sf::Sprite customer_window;
	sf::Sprite desk;
	//sf::Sprite computer;
	//sf::Sprite monitor;
	sf::Sprite keyboard;
	//sf::Sprite telephone;

public:
	GameState(gm::gameDataRef data);
	~GameState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;
};