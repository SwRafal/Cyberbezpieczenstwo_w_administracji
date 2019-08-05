#include "Battery.h"
#include <winscard.h>

Battery::Battery(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(*texture);
	this->setPosition(sf::Vector2f(BATTERY_POS_X, BATTERY_POS_Y));
	_level_display.setSize(_max_level_display_size);
	this->setColor(sf::Color::Black);

	setLevel();
	_time = 0;
}

void Battery::setLevel(unsigned short level)
{
	if (level > MAX_BATTERY_LEVEL)
		_level = MAX_BATTERY_LEVEL;
	else
		_level = level;

	_level_display.setSize(sf::Vector2f(_level_display.getSize().x, (float)_level/MAX_BATTERY_LEVEL * _max_level_display_size.y));
	sf::Vector2f new_position;
	new_position.x = BATTERY_POS_X + BATTERY_WIDTH / 2 - _level_display.getSize().x / 2;
	new_position.y = BATTERY_POS_Y + BATTERY_HEIGHT / 2 - _level_display.getSize().y / 2 + (_max_level_display_size.y - _level_display.getSize().y)/2 + 3;
	_level_display.setPosition(new_position);
	//this->setColor(sf::Color(MAX_BATTERY_LEVEL - _level, _level, 20));
	_level_display.setFillColor(sf::Color(MAX_BATTERY_LEVEL - _level, _level, 20));
	
}

void Battery::draw(sf::RenderWindow &win)
{
	win.draw(_level_display);
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