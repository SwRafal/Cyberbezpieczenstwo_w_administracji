#include "Xero.h"


Xero::Xero(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(XERO_WIDTH, XERO_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(-300, 0));
}

void Xero::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}

bool Xero::putIn()
{
	if (_bussy)
		return false;
	else
	{
		_bussy = true;
		return true;
	}
}

bool Xero::takeOut()
{
	if (!_bussy)
		return false;
	else
	{
		_bussy =false;
		return true;
	}
}