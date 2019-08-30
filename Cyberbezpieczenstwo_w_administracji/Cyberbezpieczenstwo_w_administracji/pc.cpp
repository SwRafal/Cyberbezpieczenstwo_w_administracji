#include "pc.h"


pc::pc()
{
	gm::Assets::LoadTexture("screen off small", PC_SCREEN_OFF_SMALL);
	if (gm::Assets::getTexture("screen off small") == nullptr)
		error_win_close();

	gm::Assets::LoadTexture("screen on small", PC_SCREEN_ON_SMALL);
	if (gm::Assets::getTexture("screen on small") == nullptr)
		error_win_close();

	this->setTexture(gm::Assets::getTexture("screen on small"));

	this->setSize(sf::Vector2f(SMALL_SCREEN_WIDTH, SMALL_SCREEN_HEIGHT));
	this->setIdleColor(sf::Color::White);
	this->setAimedColor(sf::Color(190, 200, 190));
	this->setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(PC_POS_X, PC_POS_Y));

	
	blackScreen.setTexture(*gm::Assets::getTexture("screen off small"));
	blackScreen.setPosition(PC_POS_X,PC_POS_Y);
	

	/* variables */

	powerOn = false;
	showBlackScreen = true;
	_opened = false;

}

pc::~pc()
{
	
}

void pc::update(sf::RenderWindow& win)
{
	if(this->aimed(win))
		blackScreen.setColor(sf::Color(190, 200, 190));
	else
		blackScreen.setColor(sf::Color::White);

	if(clicked(win))
	{
		blackScreen.setColor(sf::Color(120, 150, 120));
		if(powerOn)
		{
			open();
		}
		else if(!powerOn)
		{
			powerOn = true;
		}
	}
	
	if(powerOn)
	{
		showBlackScreen = false;
	}
	else
		showBlackScreen = true;

	


}


void pc::draw(sf::RenderWindow& win)
{
	win.draw((sf::RectangleShape)*this);

	if(showBlackScreen)
		win.draw(blackScreen);

}

void pc::turnOff()
{
	powerOn = false;
}

void pc::turnOn()
{
	powerOn = true;
}

void pc::open()
{
	_opened = true;
}

void pc::close()
{
	_opened = false;
}
