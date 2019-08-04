#include "Battery.h"
#include <winscard.h>

Battery::Battery(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(*texture);
	this->setPosition(sf::Vector2f(BATTERY_POS_X, BATTERY_POS_Y));
	this->setScale(0.6,0.6);

	setLevel();
	_time = 0;
}

void Battery::setLevel(unsigned short level)
{
	if (level > MAX_BATTERY_LEVEL)
		_level = MAX_BATTERY_LEVEL;
	else
		_level = level;

	int capacity;
	if (_level < nearly_empty)
		capacity = 1;
	else if(_level < low)
		capacity = 2;
	else if(_level < medium)
		capacity = 3;
	else
		capacity = 4;

	this->setTextureRect(sf::IntRect(capacity * BATTERY_WIDTH,0,BATTERY_WIDTH, BATTERY_HEIGHT));
	this->setColor(sf::Color(MAX_BATTERY_LEVEL - _level, _level, 20));
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
		setLevel(_level-5);

		if(prev_frame)
			prev_frame = 0;
		else
			prev_frame = 1;
	}

	if(_level < nearly_empty)
	{
		if(prev_frame)
		{
			this->setTextureRect(sf::IntRect(0,0,180.5,251));
		}
		else
		{
			this->setTextureRect(sf::IntRect(180.5,0,180.5,251));
		}
	}
}