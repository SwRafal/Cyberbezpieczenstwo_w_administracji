#include "card.h"

Card::Card(sf::Texture* texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(CARD_WIDTH, CARD_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));

	_active = false;
}

Card::~Card()
{
}

void Card::setActiveFlag(bool state)
{
	_active = state;
}
void Card::setActive()
{
	_active = true;
}
void Card::setInactive()
{
	_active = false;
}
void Card::switchActivation()
{
	_active = !_active;
}

void Card::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}
void Card::update(sf::RenderWindow &win)
{
	if (clicked(win))
	{
		switchActivation();
	}
	if (_active)
	{
		sf::Vector2f next_pos = sf::Vector2f(sf::Mouse::getPosition(win).x - CARD_WIDTH/2, sf::Mouse::getPosition(win).y - CARD_HEIGHT/2);
		setPosition(win.mapPixelToCoords((sf::Vector2i)next_pos));
	}
	else
	{
		if (getPosition().y < DESK_BEGIN - CARD_HEIGHT)
			move(0, CARD_GRAVITY);
	}
}
