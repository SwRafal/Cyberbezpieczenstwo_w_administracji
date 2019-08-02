#include "Coffee.h"

/*Maintenance(? ) */

Coffee::Coffee(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(COFFEE_WIDTH, COFFEE_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(COFFEE_POS_X, COFFEE_POS_Y));

	setLevel();
}

void Coffee::setLevel(unsigned short level)
{
	if (level > MAX_COFFEE_LEVEL)
		level = MAX_COFFEE_LEVEL;
	else
		_level = level;
}

void Coffee::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}
bool Coffee::update_drunk(sf::RenderWindow &win)
{
	if (clicked(win))
	{
		if (_level > 0)
		{
			_level--;
			//Drink sound
			return true;
		}
		else
		{
			//Denied drinking sound
		}
	}
	return false;
}