#include "textBubble.h"




textBubble::textBubble(sf::Texture *tex) : text(*gm::Assets::getFont())
{
	if (tex == nullptr)
		error_win_close();

	this->setTexture(*tex);

	text.setTextSize(20);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color::Transparent);

	text.setSize(this->getGlobalBounds().width * 0.98,this->getGlobalBounds().height * 96);


	appearing = false;
	disappearing = true;
	showText = false;

	
	scale = 0.05;
	this->setScale(scale,scale);

	posx = this->getPosition().x;
	posy = this->getPosition().y;
}

void textBubble::setBubblePosition(int x, int y)
{
	posx = x;
	posy = y;
	this->setPosition(x,y);
	text.setPosition(x + 5,y + 1);
	
}

void textBubble::keepInPlace()
{
	this->setPosition(posx - this->getGlobalBounds().width/2,posy - this->getGlobalBounds().height / 2);
}


void textBubble::animate()
{
	if(scale < 1)
		showText = false;
	if(appearing)
	{
		if(scale < 1)
		{
			scale = scale + 0.05;
			this->setScale(scale,scale);
			keepInPlace();
			if(scale >= 1.0)
			{
				showText = true;
				text.setPosition(posx - this->getGlobalBounds().width/2 + (this->getGlobalBounds().width * 0.01) , posy - this->getGlobalBounds().height / 2 + (this->getGlobalBounds().height * 0.01));
				text.setSize(this->getGlobalBounds().width * 0.98,this->getGlobalBounds().height * 0.98);
				appearing = false;
			}
		}
	}

	if(disappearing)
	{
		if(scale >= 0.0)
		{
			scale = scale - 0.05;
			this->setScale(scale,scale);
			keepInPlace();
			if(scale <= 0.0)
				disappearing = false;
		}
	}
}

void textBubble::draw(sf::RenderWindow& win) 
{
	win.draw(*this);
	if(showText)
		text.draw(win);
}

void textBubble::closeBubble()
{
	if(appearing)
		appearing = false;
	disappearing = true;
}

void textBubble::showBubble()
{
	if(disappearing)
		disappearing = false;
	appearing = true;
}

void textBubble::changeText(sf::String str)
{
	text.setTextString(str);
}



textBubble::~textBubble()
{
}
