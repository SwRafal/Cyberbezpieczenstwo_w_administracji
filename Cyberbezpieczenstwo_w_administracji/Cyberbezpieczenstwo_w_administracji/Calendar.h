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
	enum MONTHS
	{
		MONTHS_NONE = 0, JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE,
		JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
	};
	friend MONTHS operator++(MONTHS& m, int);
	friend MONTHS operator+(MONTHS& m, unsigned int n);

	enum WEEKDAYS
	{
		WEEKDAYS_NONE = 0, MONDAY, TUESDAY, WEDNESDAY,
		THURSDAY, FRIDAY, SATURDAY, SUNDAY
	};
	friend WEEKDAYS operator++(WEEKDAYS& w, int);
	friend WEEKDAYS operator+(WEEKDAYS& w, unsigned int n);

private:
	MONTHS _month;
	unsigned short _day;
	WEEKDAYS _weekday;

	sf::Text _month_txt;
	sf::Text _day_txt;
	sf::Text _weekday_txt;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Calendar(sf::Font *font, sf::Texture *texture, MONTHS month = JANUARY, unsigned short day = 1, WEEKDAYS weekday = MONDAY);

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f &offset);

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);

	void setMonth(const MONTHS month);
	void setDay(unsigned short day);
	void setWeekDay(const WEEKDAYS weekday);

	MONTHS getMonth() { return _month; }
	unsigned short getDay() { return _day; }
	WEEKDAYS getWeekDay() { return _weekday; }
};