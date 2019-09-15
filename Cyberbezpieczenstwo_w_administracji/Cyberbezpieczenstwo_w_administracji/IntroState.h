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
	gm::SelfWrittingText message2;

	sf::Text title;
	

	bool initialized;
	bool nextState;

	gm::TextButton choice1,choice2,choice3;
	

	int state;

	bool delay;

	sf::Sound click;


	sf::Sprite Icon1,Icon2,Icon3;
};
