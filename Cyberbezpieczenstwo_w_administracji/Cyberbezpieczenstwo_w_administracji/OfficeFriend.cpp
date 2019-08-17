#include "OfficeFriend.h"

/*Maintenance(?)*/

OfficeFriend::OfficeFriend(sf::Texture *texture) : text(*gm::Assets::getFont())
{
	appearing = false;
	disappearing = false;
	ready = false;

	if (texture == nullptr)
		error_win_close();

	this->setTexture(*texture);

	this->setPosition(POS_X,POS_Y);


	chat.setTexture(*gm::Assets::getTexture("chat bubble"));

	chat.setPosition(FINAL_POS_X- chat.getGlobalBounds().width + 15,POS_Y - 40);

	text.setTextSize(20);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color(255,0,0,100));
	text.setPosition(FINAL_POS_X- chat.getGlobalBounds().width + 15 + 3,POS_Y - 40 + 2);
	text.setSize(chat.getGlobalBounds().width * 0.9,chat.getGlobalBounds().height * 0.97);

	//test
	text.setTextString(L"maciek");
}


OfficeFriend::~OfficeFriend()
{
}

void OfficeFriend::animate()
{
	if(appearing)
	{
		if(this->getPosition().x > FINAL_POS_X)
		{
			this->move(-10,0);
			if(this->getPosition().x == FINAL_POS_X)
				ready = true;
		}
	}

	if(disappearing)
	{
		ready = false;
		if(this->getPosition().x < SCREEN_WIDTH + this->getGlobalBounds().width)
		{
			this->move(10,0);
			
		}
		else
			disappearing = false;
	}
}

void OfficeFriend::show()
{
	if(disappearing)
		disappearing = false;
	appearing = true;
}

void OfficeFriend::hide()
{
	if(appearing)
		appearing = false;
	disappearing = true;
}


void OfficeFriend::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
	if(ready)
	{
		win.draw(chat);
		//text.draw(win);
		sf::RenderWindow * w = &win;
		text.draw(*w);
	}
}

bool OfficeFriend::nextLine()
{	
	if(!text_queue.empty())
	{
	    text.setTextString(text_queue.front());
		text_queue.pop();
		return true;
	}
	return false;
}

void OfficeFriend::addToQueue(sf::String str)
{
	text_queue.push(str);
}