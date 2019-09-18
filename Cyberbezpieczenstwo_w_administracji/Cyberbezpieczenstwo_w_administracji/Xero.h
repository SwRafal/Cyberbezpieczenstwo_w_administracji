#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define XERO_POS_X 910
#define XERO_POS_Y 120
#define XERO_WIDTH 293
#define XERO_HEIGHT 343

class Xero : public gm::Button
{
private:
	bool _bussy;

public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;

	Xero(sf::Texture *texture);

	void draw(sf::RenderWindow &win);
	
	bool putIn();//True if succesful
	bool takeOut();//True if succesful

	bool isBussy() { return _bussy; }
};