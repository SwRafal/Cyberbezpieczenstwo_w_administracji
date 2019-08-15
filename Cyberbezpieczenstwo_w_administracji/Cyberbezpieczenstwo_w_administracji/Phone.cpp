#include "Phone.h"

/*Maintenance(?)*/

Phone::Phone(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(PHONE_WIDTH, PHONE_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(PHONE_POS_X, PHONE_POS_Y));
}


Phone::~Phone()
{
}
