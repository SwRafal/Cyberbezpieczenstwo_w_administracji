#include "pc.h"


pc::pc()
{
	gm::Assets::LoadTexture("screen off small", PC_SCREEN_OFF_SMALL);
	if (gm::Assets::getTexture("screen off small") == nullptr)
		error_win_close();
	else
	{
		this->setTexture(gm::Assets::getTexture("screen off small"));
	}

	gm::Assets::LoadTexture("screen on small", PC_SCREEN_ON_SMALL);
	if (gm::Assets::getTexture("screen on small") == nullptr)
		error_win_close();


	/* variables */

	powerOn = false;
	
}

pc::~pc()
{
	
}

void pc::update(sf::RenderWindow& win)
{
	
	if(powerOn)
	{
		this->setTexture(gm::Assets::getTexture("screen on small"));
	}
	else
		this->setTexture(gm::Assets::getTexture("power off small"));

	if


}


