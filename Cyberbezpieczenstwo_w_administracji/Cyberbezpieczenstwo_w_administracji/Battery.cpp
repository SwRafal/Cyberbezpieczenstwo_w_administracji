#include "Battery.h"

Battery::Battery(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(*texture);
	this->setPosition(sf::Vector2f(BATTERY_POS_X, BATTERY_POS_Y));

	setLevel();
	_time = 0;
}

void Battery::setLevel(unsigned short level)
{
	if (level > MAX_BATTERY_LEVEL)
		level = MAX_BATTERY_LEVEL;
	else
		_level = level;

	this->setColor(sf::Color(MAX_BATTERY_LEVEL - _level, _level, 0));
}

void Battery::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
}
bool Battery::update_empty(sf::Clock &clk)
{
	if (_level == 0)
		return true;

	if (clk.getElapsedTime().asSeconds() >= _time + 1)
	{
		_time = clk.getElapsedTime().asSeconds();
		setLevel(_level-1);
	}
}