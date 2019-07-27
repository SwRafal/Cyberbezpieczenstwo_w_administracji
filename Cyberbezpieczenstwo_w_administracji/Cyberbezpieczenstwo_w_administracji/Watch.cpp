#include "Watch.h"

Watch::Watch(sf::Font *font, sf::Texture *texture, unsigned short hours, unsigned short minutes)
{
	if (font == nullptr || texture == nullptr)
		error_win_close();

	this->setTexture(*texture);
	this->setPosition(sf::Vector2f(WATCH_POS_X, WATCH_POS_Y));

	_hour_txt.setFont(*font);
	_hour_txt.setCharacterSize(HOUR_FONT_SIZE);
	_hour_txt.setFillColor(sf::Color::Black);

	setHour(hours, minutes);

	_time = 0;
}

/*Overrides*/
void Watch::setPosition(float x, float y)
{
	sf::Sprite::setPosition(x, y);
	sf::Vector2f new_hour_pos;	
	new_hour_pos.x = this->getPosition().x + (this->getTexture()->getSize().x - _hour_txt.getLocalBounds().width - _hour_txt.getLocalBounds().left) / 2;
	new_hour_pos.y = this->getPosition().y + HOUR_POS_Y;
	_hour_txt.setPosition(new_hour_pos);
}
void Watch::setPosition(const sf::Vector2f &position)
{
	this->setPosition(position.x, position.y);
}
void Watch::move(float offsetX, float offsetY)
{
	this->setPosition(this->getPosition().x + offsetX, this->getPosition().y + offsetY);
}
void Watch::move(const sf::Vector2f &offset)
{
	this->setPosition(this->getPosition() + offset);
}

/*Setter*/
void Watch::setHour(unsigned short hour, unsigned short minute)
{
	/*Data control*/
	if (minute < 0)//Minutes
		minute = 0;
	if (minute > 59)
	{
		minute = 0;
		hour++;
	}
	if (hour < 0 || hour>23)//Hours
		hour = 0;

	_hours = hour;
	_minutes = minute;

	/*Hour string*/
	sf::String string = "";
	if (_hours < 10)
		string += " ";
	string += std::to_string(_hours);
	string += ":";
	if (_minutes < 10)
		string += "0" + std::to_string(_minutes);
	else
		string += std::to_string(_minutes);

	_hour_txt.setString(string);
}

/*Draw & Update*/
void Watch::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
	win.draw(_hour_txt);
}

void Watch::update(sf::Clock &clk)
{
	//Elapsing time
	if (clk.getElapsedTime().asSeconds() > _time + 1)
	{
		_time = clk.getElapsedTime().asSeconds();
		_minutes++;
		setHour(_hours, _minutes);
	}
}