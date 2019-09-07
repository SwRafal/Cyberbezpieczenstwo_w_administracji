#pragma once
#include "Engine/Engine.h"
#include "card.h"

#define CARD_READER_WIDTH 145
#define CARD_READER_HEIGHT 100
#define CARD_READER_POS_X 0
#define CARD_READER_POS_Y 490


class CardReader
{
private:
	gm::Button cardIn;
	gm::Button cardOut;

	Card *card = nullptr;

	bool cardInside;
	
public:
	bool hidden;

	bool isCardInside();

	void changeState();

	void update();

	void draw(sf::RenderWindow &win);

	void setPosition(int x,int y);

	CardReader(Card *card_ref);
	~CardReader();


};
