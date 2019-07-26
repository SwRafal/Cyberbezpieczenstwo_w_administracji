#include "Calendar.h"

Calendar::Calendar(sf::Font *font, sf::Texture *texture, sf::String month, sf::String day, sf::String weekday)
{
	if (font == nullptr || texture == nullptr)
		error_win_close();

	this->setTexture(*texture);
	this->setPosition(sf::Vector2f(CALENDAR_POS_X, CALENDAR_POS_Y));

	_month.setFont(*font);
	_month.setCharacterSize(MONTH_FONT_SIZE);
	_month.setFillColor(sf::Color::Black);
	_month.setString(month);

	_day.setFont(*font);
	_day.setCharacterSize(DAY_FONT_SIZE);
	_day.setFillColor(sf::Color::Black);
	_day.setString(day);

	_weekday.setFont(*font);
	_weekday.setCharacterSize(WEEKDAY_FONT_SIZE);
	_weekday.setFillColor(sf::Color::Black);
	_weekday.setString(weekday);
}

/*Overrites*/
void Calendar::setPosition(float x, float y)
{
	sf::Sprite::setPosition(x, y);
	sf::Vector2f new_month_pos;
	new_month_pos.x = (TEXTURE_OFFSET + this->getPosition().x + this->getTexture()->getSize().x - _month.getLocalBounds().width - _month.getLocalBounds().left) / 2;
	new_month_pos.y = this->getPosition().y + MONTH_POS_Y;
	_month.setPosition(new_month_pos);

	sf::Vector2f new_day_pos;
	new_day_pos.x = (TEXTURE_OFFSET + this->getPosition().x + this->getTexture()->getSize().x - _day.getLocalBounds().width - _day.getLocalBounds().left) / 2;
	new_day_pos.y = this->getPosition().y + DAY_POS_Y;
	_day.setPosition(new_day_pos);

	sf::Vector2f new_weekday_pos;
	new_weekday_pos.x = (TEXTURE_OFFSET + this->getPosition().x + this->getTexture()->getSize().x - _weekday.getLocalBounds().width - _weekday.getLocalBounds().left) / 2;
	new_weekday_pos.y = this->getPosition().y + WEEKDAY_POS_Y;
	_weekday.setPosition(new_weekday_pos);
}
void Calendar::setPosition(const sf::Vector2f &position)
{
	this->setPosition(position.x, position.y);
}
void Calendar::move(float offsetX, float offsetY)
{
	this->setPosition(this->getPosition().x + offsetX, this->getPosition().y + offsetY);
}
void Calendar::move(const sf::Vector2f &offset) 
{
	this->setPosition(this->getPosition()+offset);
}

/*Setters*/
void Calendar::setMonth(const sf::String month)
{
	_month.setString(month);
}
void Calendar::setDay(const sf::String day)
{
	_day.setString(day);
}
void Calendar::setWeekDay(const sf::String weekday)
{
	_weekday.setString(weekday);
}

/*Draw & Update*/
void Calendar::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
	win.draw(_month);
	win.draw(_day);
	win.draw(_weekday);
}

void Calendar::update(sf::RenderWindow &win)
{

}