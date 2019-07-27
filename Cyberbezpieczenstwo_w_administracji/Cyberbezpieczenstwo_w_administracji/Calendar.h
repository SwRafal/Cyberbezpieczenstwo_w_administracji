#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define CALENDAR_POS_X 1155
#define CALENDAR_POS_Y 20

#define MONTH_POS_Y 15 //Offset from calendar's position
#define MONTH_FONT_SIZE 18

#define DAY_POS_Y 45 //Offset from calendar's position
#define DAY_FONT_SIZE 36

#define WEEKDAY_POS_Y 100 //Offset from calendar's position
#define WEEKDAY_FONT_SIZE 18

#define TEXTURE_OFFSET 10 //Calencar on texture start at 10th pixel in png file

class Calendar : public sf::Sprite
{
private:
	sf::Text _month;
	sf::Text _day;
	sf::Text _weekday;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Calendar(sf::Font *font, sf::Texture *texture, sf::String month = L"Styczeñ", sf::String day = "1", sf::String weekday = "pon.");

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f &offset);

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);

	void setMonth(const sf::String month);
	void setDay(const sf::String day);
	void setWeekDay(const sf::String weekday);

	sf::String getMonth() { return _month.getString(); }
	sf::String getDay() { return _day.getString(); }
	sf::String getWeekDay() { return _weekday.getString(); }
};