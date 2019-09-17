#pragma once
#include <queue>

#include "Engine/Engine.h"
#include "Game.h"
#include "Functions.h"
#include "GameStateItems.h"
#include "Days.h"
#include "PauseState.h"
#include "dayx.h"
#include "textBubble.h"
#include "OfficeFriend.h"
#include "ChoiceButton.h"
#include "Eyelids.h"
#include "OfficeApplicant.h"
#include "Mobile.h"
#include "Document.h"
#include "OpenedDoc.h"

#define GAMELOST_INFO_TIME 5000

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

	gm::TextField *textField;

	textBubble *popUpText;
	int time;

	//OfficeFriend *officeLady;
	OfficeApplicant *officeLady;
	OfficeApplicant *officeApplicant = nullptr;


	Eyelids *eyelids = nullptr;

	/*Settings*/
	unsigned int day;
	bool initialized;
	bool nextDay;

	/*Environment*/
	sf::Sprite wall;
	sf::Sprite desk;
	Calendar *calendar = nullptr;
	//sf::Sprite telephone;
	Watch *watch = nullptr;
	Coffee *coffee = nullptr;
	Battery *battery = nullptr;
	Bell *bell = nullptr;
	Phone *phone = nullptr;
	Mobile *mobile = nullptr;
	Card *card = nullptr;
	CardReader *cardReader = nullptr;
	Document *doc = nullptr;
	OpenedDoc *open_doc = nullptr;

	pc *computer = nullptr;
	OpenPC *openedcomputer = nullptr;

	const sf::Vector2f yes_stamp_pos = sf::Vector2f(360,490);
	Stamp *yes_stamp = nullptr;
	const sf::Vector2f no_stamp_pos = sf::Vector2f(330, 460);
	Stamp *no_stamp = nullptr;

	Book *book = nullptr;
	OpenedBook *openedbook = nullptr;

	Bin *bin = nullptr;
	sf::Sprite sushi;
	sf::Sprite rj45;

	PlayerIcon playerIco;
	

	ChoiceButton *choice1,*choice2,*choice3,*choice4;

	/*LOST GAME*/
	bool lost = false;
	bool naganiony = false;
	sf::Int32 info_time;
	sf::Text *gamelost_info = nullptr;
	sf::Text *nagana_info = nullptr;

	/*CUSTOM DAYS*/
	Day_0 *day0 = nullptr;
	Day_1 *day1 = nullptr;/*!!!to musi byc wskaznik jezeli wzajemnie klasy sie includuja!!!*/
	Day_2 *day2 = nullptr;
	Day_3 *day3 = nullptr;

	void gameover(sf::String reason);

public:
	GameState(gm::gameDataRef data);
	~GameState();

	void init() override;
	void handleInput() override;
	void update(sf::RenderWindow &win) override;
	void draw(sf::RenderWindow& win) override;

	friend class Day;
	friend class Day_0;
	friend class Day_1;
	friend class Day_2;
	friend class Day_3;
};