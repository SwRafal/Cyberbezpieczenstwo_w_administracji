#pragma once
#include "Day.h"
#include "OfficeFriend.h"
#include "OfficeApplicant.h"


#define THOUGHT_TIME 3000

class Day_2 : public Day
{
public:
	int state;

	bool init;
	bool initDelay;
	bool showButtons;
	

	//quests / info
	bool coffeeClicked;
	bool bookOpened;
	bool photosSent;

	//other variables
	int offset;
	int time;

	//phone text
	bool displayPhoneText;
	sf::Sprite bg;
	sf::Text phoneText;

	bool displayWorkPhoneText;
	sf::Sprite bgWork;
	sf::Text workPhoneText;

	//thief
	sf::Sprite thief;
	sf::Texture thiefTex;

	//dark screen
	sf::RectangleShape darkScreen;
	bool showDarkScreen;

	//info - blank text
	sf::Text blankInfo;
	bool showInfo;

	//used for text with character name;
	sf::String temp;

	//characters
	OfficeApplicant *itGuy;
	OfficeApplicant *boss;

	//pendrive
	sf::Sprite pendrive;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	Day_2();
	~Day_2();

	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};
