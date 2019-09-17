#pragma once
#include "Game.h"
#include "Engine/Engine.h"

#define LOADING_BAR_FULL_SIZE 782

class GameOverState : public gm::SlideFrame 
{
private:
	gm::gameDataRef data;
public:
	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;

	sf::Font arial;
	sf::Text loadingText;
	sf::RectangleShape loadingBar;
	sf::Sprite background;

	gm::Button next;
	gm::Information reason;

	int state;
	int loadingNumber;
	int loadingBarSize;

	bool animated;

	GameOverState(gm::gameDataRef data);
	~GameOverState();
};

