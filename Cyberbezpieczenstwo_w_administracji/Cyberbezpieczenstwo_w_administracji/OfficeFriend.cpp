#include "OfficeFriend.h"

/*Maintenance(?)*/

OfficeFriend::OfficeFriend(sf::Texture *texture) : text(*gm::Assets::getFont())
{
	appearing = false;
	disappearing = false;
	ready = false;

	clicked = false;

	if (texture == nullptr)
		error_win_close();

	this->setTexture(*texture);

	this->setPosition(POS_X,POS_Y);


	chat.setTexture(*gm::Assets::getTexture("chat bubble"));
	chat.setPosition(FINAL_POS_X- chat.getGlobalBounds().width + 15,POS_Y - 40);

	text.setTextSize(20);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color::Transparent);
	text.setPosition(FINAL_POS_X- chat.getGlobalBounds().width + 15 + 3,POS_Y - 40 + 2);
	text.setSize(chat.getGlobalBounds().width * 0.9,chat.getGlobalBounds().height * 0.97);

	
	img.setTexture(*gm::Assets::getTexture("arrow"));
	img.setColor(sf::Color::Black);
	img.setScale(0.3,0.3);
	img.setPosition(sf::Vector2f(chat.getPosition().x + chat.getGlobalBounds().width * 0.85,chat.getPosition().y + chat.getGlobalBounds().height * 0.72 ));

	button.setSize(sf::Vector2f(img.getGlobalBounds().width,img.getGlobalBounds().height));
	button.setPosition(img.getPosition());
	
	
	
	button.setIdleColor(sf::Color::Transparent);
	button.setAimedColor(sf::Color::Transparent);
	button.setPressColor(sf::Color::Transparent);
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

	if(button.clicked(gm::Core::getWindow()))
	{
		img.setColor(sf::Color::Black);
		this->nextLine();
	}
	else if(button.aimed(gm::Core::getWindow()))
	{
		img.setColor(sf::Color(0, 255, 85,255));
	}
	else
	{
		img.setColor(sf::Color(0, 255, 162,255));
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
		sf::RenderWindow * w = &win;
		text.draw(*w);
		win.draw(img);
		win.draw((sf::RectangleShape)button);
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