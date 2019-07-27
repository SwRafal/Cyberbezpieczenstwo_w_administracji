#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define WATCH_POS_X 595
#define WATCH_POS_Y 20

#define HOUR_POS_Y 40 //Offset from watch's position
#define HOUR_FONT_SIZE 36

class Watch : public sf::Sprite
{
private:
	sf::Text _hour_txt;
	unsigned short _hours;
	unsigned short _minutes;
	float _time;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Watch(sf::Font *font, sf::Texture *texture, unsigned short hours = 8, unsigned short minutes = 0);

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f &offset);

	void draw(sf::RenderWindow &win);
	void update(sf::Clock &clk);

	void setHour(unsigned short hour, unsigned short minute);

	sf::String getHourString() { return _hour_txt.getString(); }
	unsigned short getHours() { return _hours; }
	unsigned short getMinutes() { return _minutes; }
};