#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define STAMP_WIDTH 109
#define STAMP_HEIGHT 141

#define STAMP_GRAVITY 20
#define DESK_BEGIN 520 //The height level (from top) desk starts at

class Stamp : public gm::Button
{
	bool _active;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Stamp(sf::Texture *texture);
	~Stamp();

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);

	void setActiveFlag(bool state);
	void setActive();
	void setInactive();
	void switchActivation();/*Negate the 'active' flag*/

	bool isActive() { return _active; }
};

