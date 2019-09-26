#include "OfficeApplicant.h"

/*Maintenance(?)*/

OfficeApplicant::OfficeApplicant(sf::Texture *texture) : text(*gm::Assets::getFont())
{
	appearing = false;
	disappearing = false;
	ready = false;
	active = true;
	hidden = false;

	state = 0;

	clicked = false;

	if (texture == nullptr)
		error_win_close();

	this->setTexture(*texture);

	this->setPosition(POS_X, POS_Y);


	chat.setTexture(*gm::Assets::getTexture("chat bubble"));
	chat.setPosition(FINAL_POS_X - chat.getGlobalBounds().width + 15, POS_Y + 10);

	text.setTextSize(16);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color::Transparent);
	text.setPosition(FINAL_POS_X - chat.getGlobalBounds().width + 15 + 3, POS_Y + 12);
	text.setSize(chat.getGlobalBounds().width * 0.9, chat.getGlobalBounds().height * 0.97);


	img.setTexture(*gm::Assets::getTexture("arrow"));
	img.setColor(sf::Color::Black);
	img.setScale(0.3, 0.3);
	img.setPosition(sf::Vector2f(chat.getPosition().x + chat.getGlobalBounds().width * 0.85, chat.getPosition().y + chat.getGlobalBounds().height * 0.72));

	button.setSize(sf::Vector2f(img.getGlobalBounds().width, img.getGlobalBounds().height));
	button.setPosition(img.getPosition());



	button.setIdleColor(sf::Color::Transparent);
	button.setAimedColor(sf::Color::Transparent);
	button.setPressColor(sf::Color::Transparent);

}


OfficeApplicant::~OfficeApplicant()
{
}

void OfficeApplicant::animate()
{
	if (appearing)
	{
		hidden = false;
		if (this->getPosition().x > FINAL_POS_X)
		{
			this->move(-10, 0);
			if (this->getPosition().x == FINAL_POS_X)
				ready = true;
		}
	}

	if (disappearing)
	{
		ready = false;
		if (this->getPosition().x < SCREEN_WIDTH + this->getGlobalBounds().width)
		{
			this->move(10, 0);

		}
		else
		{
			disappearing = false;
			hidden = true;
		}
			
	}

	if (ready)
	{
		if (active)
		{
			if (button.clicked(gm::Core::getWindow()))
			{
				img.setColor(sf::Color::Black);
				this->nextLine();
			}
			else if (button.aimed(gm::Core::getWindow()))
			{
				img.setColor(sf::Color(0, 255, 85, 255));
			}
			else
			{
				img.setColor(sf::Color(0, 255, 162, 255));
			}
		}
	}


}

void OfficeApplicant::show()
{
	if (disappearing)
		disappearing = false;
	appearing = true;
}

void OfficeApplicant::hide()
{
	if (appearing)
		appearing = false;
	disappearing = true;
}


void OfficeApplicant::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
	if (ready)
	{
		win.draw(chat);
		sf::RenderWindow * w = &win;
		text.draw(*w);
		if(active)
		{
			win.draw(img);
			win.draw((sf::RectangleShape)button);	
		}
		
	}
}

bool OfficeApplicant::nextLine()
{
	if (!text_queue.empty())
	{
		text.setTextString(text_queue.front());
		text_queue.pop();
		state++;
		return true;
	}
	return false;
}

void OfficeApplicant::addToQueue(sf::String str)
{
	text_queue.push(str);
}

void OfficeApplicant::setButtonActive()
{
	active = true;
}


void OfficeApplicant::setButtonInactive()
{
	active = false;
}

void OfficeApplicant::moveChatBox(int x, int y)
{
	chat.setPosition(chat.getPosition().x + x,chat.getPosition().y + y);
	text.setPosition(text.getPosition().x + x , text.getPosition().y + y);
	img.setPosition(img.getPosition().x + x , img.getPosition().y + y);
	button.setPosition(button.getPosition().x + x , button.getPosition().y + y);

}
