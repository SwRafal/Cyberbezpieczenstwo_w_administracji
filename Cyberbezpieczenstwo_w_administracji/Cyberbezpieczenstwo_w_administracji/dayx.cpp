#include "dayx.h"
#include "Definitions.h"
#include "Engine/Assets.h"


dayx::dayx(int &_dayNumber)
{
	finished = false;
	opacitySpeed = 5;
	show = false;
	timer = 0;
	opacity = 0;
	dayNumber = &_dayNumber;
	this->setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
	this->setFillColor(sf::Color(0,0,0,0));
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Style::Bold);
	title.setFont(*gm::Assets::getFont());
	title.setCharacterSize(80);
	title.setString(L"Dzieñ  ");
	title.setString(title.getString() + std::to_string(*dayNumber));
	title.setPosition(SCREEN_WIDTH /2 - title.getGlobalBounds().width /2 , SCREEN_HEIGHT / 2 - title.getGlobalBounds().height/2);

	gm::Assets::LoadTexture("sunrise", "resources/textures/sunrise.png");
	background.setTexture(*gm::Assets::getTexture("sunrise"));
	
}


dayx::~dayx()
{
}

void dayx::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		//target.draw((sf::RectangleShape)*this,states);
		target.draw(background);
		if(show)
			target.draw(title);
	}

void dayx::update()
{
	if(timer == 200)
	{
		show = false;
		if(opacity > 0)
		{
			opacity = opacity - opacitySpeed;
			background.setColor(sf::Color(255,255,255,opacity));
			//this->setFillColor(sf::Color(0,0,0,opacity));

		}

		if(opacity == 0)
			finished = true;
	}

	if(opacity < 255 && timer!= 200)
		opacity = opacity + opacitySpeed;
	if(opacity <= 255)
		background.setColor(sf::Color(255,255,255,opacity));
		//this->setFillColor(sf::Color(0,0,0,opacity));

	if(opacity == 255 && timer < 200)
	{
		show = true;
		timer++;
	}
}

void dayx::reset()
{
	show = false;
	timer = 0;
	opacity = 0;
	finished = false;
}

void dayx::nextDay()
{
	this->reset();
	(*dayNumber)++;
	title.setString(L"Dzieñ  ");
	title.setString(title.getString() + std::to_string(*dayNumber));
}
