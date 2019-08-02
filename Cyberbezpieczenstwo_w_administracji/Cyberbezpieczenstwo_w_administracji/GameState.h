#pragma once
#include "Engine/Engine.h"
#include "Game.h"
#include "Functions.h"
#include "GameStateItems.h"
#include "PauseState.h"

void error_win_close();

class GameState : public gm::SlideFrame
{
private:
	gm::gameDataRef data;

	/*Settings*/
	unsigned int day;

	/*Environment*/
	sf::Sprite wall;
	Calendar *calendar = nullptr;
	//sf::Sprite telephone;
	Watch *watch = nullptr;
	Coffee *coffee = nullptr;
	Battery *battery = nullptr;
	Bell *bell = nullptr;

	const sf::Vector2f yes_stamp_pos = sf::Vector2f(250,490);
	Stamp *yes_stamp = nullptr;
	const sf::Vector2f no_stamp_pos = sf::Vector2f(220, 460);
	Stamp *no_stamp = nullptr;

public:
	GameState(gm::gameDataRef data);
	~GameState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;
};