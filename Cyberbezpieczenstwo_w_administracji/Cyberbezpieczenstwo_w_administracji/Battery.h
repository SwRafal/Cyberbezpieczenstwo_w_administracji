#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define BATTERY_POS_X 1160
#define BATTERY_POS_Y 560
#define BATTERY_WIDTH 180.5
#define BATTERY_HEIGHT 251

#define MAX_BATTERY_LEVEL 200

enum battery_capacity
{
	nearly_empty = MAX_BATTERY_LEVEL/4,
	low = MAX_BATTERY_LEVEL/2,
	medium = 3*MAX_BATTERY_LEVEL/4,
	high = MAX_BATTERY_LEVEL
};

class Battery : public sf::Sprite
{
private:
	unsigned short _level;
	float _time;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Battery(sf::Texture *texture);

	void draw(sf::RenderWindow &win);
	bool update_empty(sf::Clock &clk);//Returns bool value, so GameState knows if we ran out of energy

	void setLevel(unsigned short level = MAX_BATTERY_LEVEL);

	unsigned short getLevel() { return _level; }

	battery_capacity capacities;
	int prev_frame = 1;
};