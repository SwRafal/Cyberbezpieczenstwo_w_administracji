#include "Stamp.h"

Stamp::Stamp(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(STAMP_WIDTH, STAMP_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));

	_active = false;
}


Stamp::~Stamp()
{
}

void Stamp::setActiveFlag(bool state)
{
	_active = state;
}
void Stamp::setActive()
{
	_active = true;
}
void Stamp::setInactive()
{
	_active = false;
}
void Stamp::switchActivation()
{
	_active = !_active;
}

void Stamp::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}
void Stamp::update(sf::RenderWindow &win)
{
	if (clicked(win))
	{
		switchActivation();
	}
	if (_active)
	{
		sf::Vector2f next_pos = sf::Vector2f(sf::Mouse::getPosition(win).x - STAMP_WIDTH/2, sf::Mouse::getPosition(win).y - STAMP_HEIGHT/2);
		setPosition(win.mapPixelToCoords((sf::Vector2i)next_pos));
	}
	else
	{
		if (getPosition().y < DESK_BEGIN - STAMP_HEIGHT)
			move(0, 5);
	}
}