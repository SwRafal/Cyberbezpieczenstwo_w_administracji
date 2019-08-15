#include "textBubble.h"




textBubble::textBubble(sf::Texture *tex) : text(*gm::Assets::getFont())
{
	if (tex == nullptr)
		error_win_close();

	this->setTexture(*tex);

	text.setTextSize(20);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color::Transparent);

	appearing = true;
	disappearing = false;
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
	text.setPosition(x,y);
	//text.setSize(this->getGlobalBounds().width,this->getGlobalBounds().height);
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

void textBubble::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw((sf::Sprite)*this,states);
	if(showText)
		target.draw(text);
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

void textBubble::changeText(std::string str)
{
	text.setTextString(sf::String(str));
}




textBubble::~textBubble()
{
}
