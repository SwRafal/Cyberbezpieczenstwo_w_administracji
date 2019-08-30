#include "Mobile.h"

/*Maintenance(?)*/

Mobile::Mobile() : text(*gm::Assets::getFont()), arrowButton(*gm::Assets::getFont())
{
	gm::Assets::LoadTexture("PRIVATE_PHONE", TEXTURE_PRIVATE_PHONE);
	if (gm::Assets::getTexture("PRIVATE_PHONE") == nullptr)
		error_win_close();

	this->setTexture(gm::Assets::getTexture("PRIVATE_PHONE"));

	/* set position */

	this->setSize(sf::Vector2f(MOBILE_WIDTH, MOBILE_HEIGHT));
	this->setIdleColor(sf::Color::White);
	this->setAimedColor(sf::Color(190, 200, 190));
	this->setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(MOBILE_POS_X, MOBILE_POS_Y));
}


Mobile::~Mobile()
{
}

void Mobile::draw(sf::RenderWindow& win)
{
	win.draw((sf::RectangleShape)*this);
}

void Mobile::addToQueue(sf::String str)
{
	text_queue.push(str);
}
