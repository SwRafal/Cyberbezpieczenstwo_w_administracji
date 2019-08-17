#include "dayx.h"
#include "Definitions.h"
#include "Engine/Assets.h"


dayx::dayx(int _dayNumber)
{
	opacitySpeed = 5;
	show = false;
	timer = 0;
	opacity = 0;
	dayNumber = _dayNumber;
	this->setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
	this->setFillColor(sf::Color(0,0,0,0));
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Style::Bold);
	title.setFont(*gm::Assets::getFont());
	title.setCharacterSize(80);
	title.setString(L"Dzie�  ");
	title.setString(title.getString() + std::to_string(dayNumber));
	title.setPosition(SCREEN_WIDTH /2 - title.getGlobalBounds().width /2 , SCREEN_HEIGHT / 2 - title.getGlobalBounds().height/2);
}


dayx::~dayx()
{
}

void dayx::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw((sf::RectangleShape)*this,states);
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
			this->setFillColor(sf::Color(0,0,0,opacity));

		}
	}

	if(opacity < 255 && timer!= 200)
		opacity = opacity + opacitySpeed;
	if(opacity <= 255)
		this->setFillColor(sf::Color(0,0,0,opacity));

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
}

void dayx::nextDay()
{
	this->reset();
	dayNumber++;
	title.setString(L"Dzie�  ");
	title.setString(title.getString() + std::to_string(dayNumber));
}