#pragma once
#include <queue>

#include "Engine/Engine.h"
#include "Game.h"
#include "Functions.h"
#include "GameStateItems.h"
#include "PauseState.h"
#include "dayx.h"
#include "textBubble.h"
#include "OfficeFriend.h"

void error_win_close();

struct ItemsComparator/*Comparator for priority_queues in draw and update*/
{
	bool operator()(const gm::Button *b1, const gm::Button *b2)
	{
		return b1->getPosition().y > b2->getPosition().y;
	}
};

class GameState : public gm::SlideFrame
{
private:
	gm::gameDataRef data;

	dayx *dayShowScreen;

	textBubble *test;

	OfficeFriend *officeLady;

	/*Settings*/
	unsigned int day;
	bool initialized;
	bool nextDay;

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

	Book *book = nullptr;
	OpenedBook *openedbook = nullptr;

	Bin *bin = nullptr;

	

public:
	GameState(gm::gameDataRef data);
	~GameState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;
};