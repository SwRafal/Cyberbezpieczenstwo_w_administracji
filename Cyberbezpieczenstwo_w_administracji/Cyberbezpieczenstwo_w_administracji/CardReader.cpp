#include "CardReader.h"

CardReader::CardReader(Card *card_ref)
{
	gm::Assets::LoadTexture("card in", CARD_READER_CARD_IN);
	gm::Assets::LoadTexture("card out", CARD_READER_CARD_OUT);

	cardIn.setTexture(gm::Assets::getTexture("card in"));
	cardIn.setSize(CARD_READER_WIDTH,CARD_READER_HEIGHT);
	cardIn.setPosition(CARD_READER_POS_X,CARD_READER_POS_Y);
	cardIn.setIdleColor(sf::Color::White);
	cardIn.setAimedColor(sf::Color(190, 200, 190));
	cardIn.setPressColor(sf::Color(120, 150, 120));

	cardOut.setTexture(gm::Assets::getTexture("card out"));
	cardOut.setSize(CARD_READER_WIDTH,CARD_READER_HEIGHT);
	cardOut.setPosition(CARD_READER_POS_X,CARD_READER_POS_Y);
	cardOut.setIdleColor(sf::Color::White);
	cardOut.setAimedColor(sf::Color(190, 200, 190));
	cardOut.setPressColor(sf::Color(120, 150, 120));

	card = card_ref;
	cardInside = false;
	hidden = true;

	cardIn.setPosition(0,-300);	
	cardOut.setPosition(0,-300);	
}

CardReader::~CardReader()
{
	
}

bool CardReader::isCardInside()
{
	return cardInside;
}

void CardReader::changeState()
{
	cardInside = !cardInside;
}

void CardReader::update()
{
	if(cardInside)
		card->setPosition(-200,5);

	if(cardInside)
	{
		cardIn.setPosition(CARD_READER_POS_X,CARD_READER_POS_Y);
		cardOut.setPosition(0,-300);	
	}
	else
	{
		cardOut.setPosition(CARD_READER_POS_X,CARD_READER_POS_Y);
		cardIn.setPosition(0,-300);	
	}

	if(hidden)
	{
		cardIn.setPosition(0,-300);	
		cardOut.setPosition(0,-300);	
	}

	if(cardIn.clicked(gm::Core::getWindow()))
	{
		card->setActive();
		changeState();
	}
	else if(cardOut.clicked(gm::Core::getWindow()))
	{
		if(card->getGlobalBounds().intersects(cardOut.getGlobalBounds()))
			changeState();
	}
}

void CardReader::draw(sf::RenderWindow& win)
{
	if(cardInside)
		win.draw(cardIn);
	else
		win.draw(cardOut);
}






