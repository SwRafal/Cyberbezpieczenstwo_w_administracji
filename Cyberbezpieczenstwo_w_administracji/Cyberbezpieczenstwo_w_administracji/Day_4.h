#pragma once
#include "Day.h"
#include "textBubble.h"
#include "OfficeApplicant.h"

#define LETTER_START_X 800
#define LETTER_START_Y 270
#define LETTER_FINISH_X 1070
#define LETTER_FINISH_Y 470


class Day_4 : public Day
{
public:
	int state;
	int offset;
	bool showButtons;
	bool callIn;
	bool drawDowod;

	//day start
	bool coffeeClicked = false;
	bool bookOpened = false;

	//quest 1
	bool showNewspaper;
	sf::Sprite newspaper;
	sf::Sprite dowod1;
	bool quest1completed = false;

	//quest 2
	bool quest2completed = false;

	//quest 3
	sf::Sprite letter;
	sf::Sprite letterOpen;
	sf::Sprite response;
	sf::Sprite finalResponse;
	int rChoice = 0;
	bool drawFinalResponse = false;
	bool drawLetter = false;
	bool drawLetterOpen = false;
	bool drawResponse = false;
	bool showMinigame = false;

	gm::CheckBox b1,b2,b3,b4,b5,b6,b7,b8;
	sf::Sprite checkingGameBG;

	bool selectedProperly = false;

	//koniec
	sf::Sprite endgame;
	sf::Text endtext;

	//petenci
	OfficeApplicant * petent1;
	OfficeApplicant * petent2;

	textBubble *thought = nullptr;
	sf::Int32 thought_time;

	OfficeApplicant *itGuy = nullptr;
	OfficeApplicant *boss = nullptr;

	Day_4();
	~Day_4();
	void update(GameState *gs, sf::RenderWindow &win) override;
	void draw(GameState *gs, sf::RenderWindow &win);
};