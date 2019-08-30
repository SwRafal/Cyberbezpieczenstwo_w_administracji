#include "Coffee.h"

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

	gm::Assets::LoadTexture("coffe", TEXTURE_COFFEE);
	gm::Assets::LoadTexture("coffe2", TEXTURE_COFFEE2);
	gm::Assets::LoadTexture("coffe3", TEXTURE_COFFEE3);
	gm::Assets::LoadTexture("coffe4", TEXTURE_COFFEE4);

	this->setTexture(gm::Assets::getTexture("coffe4"));

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
		this->setTexture(gm::Assets::getTexture("coffe"));
		return true;
	}
	return false;
}

void Coffee::reset()
{
	this->setTexture(gm::Assets::getTexture("coffe4"));
}
