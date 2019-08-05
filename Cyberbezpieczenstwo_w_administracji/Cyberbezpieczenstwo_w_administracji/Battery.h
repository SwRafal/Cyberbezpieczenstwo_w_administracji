#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define BATTERY_POS_X 1180
#define BATTERY_POS_Y 560
#define BATTERY_WIDTH 80
#define BATTERY_HEIGHT 160

#define MAX_BATTERY_LEVEL 200

class Battery : public sf::Sprite
{
private:
	unsigned short _level;
	float _time;
	sf::RectangleShape _level_display;
	const sf::Vector2f _max_level_display_size = sf::Vector2f( BATTERY_WIDTH - 6, BATTERY_HEIGHT - 20 );
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Battery(sf::Texture *texture);

	void draw(sf::RenderWindow &win);
	bool update_empty(sf::Clock &clk);//Returns bool value, so GameState knows if we ran out of energy

	void setLevel(unsigned short level = MAX_BATTERY_LEVEL);

	unsigned short getLevel() { return _level; }
};