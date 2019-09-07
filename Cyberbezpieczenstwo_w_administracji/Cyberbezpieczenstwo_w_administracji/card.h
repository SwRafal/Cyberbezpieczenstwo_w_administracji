#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define CARD_WIDTH 125
#define CARD_HEIGHT 92

#define CARD_GRAVITY 15
#define DESK_BEGIN 520 //The height level (from top) desk starts at

class Card : public gm::Button
{
	bool _active;
	
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Card(sf::Texture *texture);
	~Card();

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);

	void setActiveFlag(bool state);
	void setActive();
	void setInactive();
	void switchActivation();/*Negate the 'active' flag*/


	bool isActive() { return _active; }
	
};