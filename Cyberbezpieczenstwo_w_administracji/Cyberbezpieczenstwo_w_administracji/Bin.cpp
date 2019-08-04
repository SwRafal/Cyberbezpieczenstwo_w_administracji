#include "Bin.h"

/*Maintenance(? ) */

Bin::Bin(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(BIN_WIDTH, BIN_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(BIN_POS_X, BIN_POS_Y));
}

void Bin::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}