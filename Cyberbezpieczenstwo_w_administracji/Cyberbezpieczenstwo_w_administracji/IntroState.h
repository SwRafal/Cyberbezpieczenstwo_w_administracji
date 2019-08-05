#pragma once
#include "SelfWrittingText.h"
#include "Game.h"
#include "Engine/Engine.h"




class IntroState : public gm::SlideFrame
{
	private:
	gm::gameDataRef data;

public:
	IntroState(gm::gameDataRef data);
	~IntroState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;

	gm::SelfWrittingText message;
	gm::SelfWrittingText space;

	sf::Text title;
	sf::Text playerChoice;

	bool initialized;
	bool nextState;

	gm::TextButton choice1,choice2,choice3;
	gm::TextButton player1, player2, player3;

	int state;

	sf::Sound click;
	
};
