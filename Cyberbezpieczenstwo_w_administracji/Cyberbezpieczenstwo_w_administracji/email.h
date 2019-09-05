#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define EMAIL_POS_X 252
#define EMAIL_POS_Y 112

#define EMAIL_EXIT_BUTTON_POS_X 955
#define EMAIL_EXIT_BUTTON_POS_Y 69

#define EMAIL_EXIT_BUTTON_SIZE 36

class mail
{
public:
	mail();


	
//private:
	sf::Sprite email;

	gm::Button emailExit;
	bool buttonActive;

	sf::Text title;
	sf::Text sender;
	gm::Information content;


	void draw(sf::RenderWindow &win);

	void setMailButtonActive();
	void setMailButtonInactive();

	void newMail(sf::String title,sf::String sender,sf::String content);

	
};