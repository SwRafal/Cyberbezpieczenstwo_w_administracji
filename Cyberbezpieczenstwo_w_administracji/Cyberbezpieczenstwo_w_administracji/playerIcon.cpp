#include "playerIcon.h"

PlayerIcon::PlayerIcon(int character) : text(*gm::Assets::getFont())
{
	appearing = false;
	disappearing = false;
	ready = false;
	hidden = false;

	state = 0;

	switch (character)
	{
	case 0: //halina default

	case 1: //halina
		icon.setTexture(*gm::Assets::getTexture("halinaIcon"));
		break;
	case 2: //haker
		icon.setTexture(*gm::Assets::getTexture("hakerIcon"));
		break;
	case 3: //mag
		icon.setTexture(*gm::Assets::getTexture("magIcon"));
		break;
	}

	icon.setScale(0.35,0.35);
	icon.setPosition(POS_X,POS_Y);

	gm::Assets::LoadTexture("playerChat", PLAYER_CHAT_BUBBLE);
	chat.setTexture(*gm::Assets::getTexture("playerChat"));
	chat.setPosition(FINAL_POS_X - 25 + icon.getGlobalBounds().width,POS_Y);

	text.setTextSize(20);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color::Transparent);
	text.setPosition(FINAL_POS_X + chat.getPosition().x + 22, POS_Y + 3);
	text.setSize(chat.getGlobalBounds().width * 0.87, chat.getGlobalBounds().height * 0.95);


}

PlayerIcon::~PlayerIcon()
{
	
}

void PlayerIcon::show()
{
	appearing = true;
	disappearing = false;
}

void PlayerIcon::hide()
{
	disappearing = true;
	appearing = false;
}

bool PlayerIcon::nextLine()
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

void PlayerIcon::addToQueue(sf::String str)
{
	text_queue.push(str);
}

void PlayerIcon::animate()
{
	if (appearing)
	{
		hidden = false;
		if (icon.getPosition().x < FINAL_POS_X)
		{
			icon.move(10, 0);
			if (icon.getPosition().x == FINAL_POS_X)
				ready = true;
		}
	}

	if (disappearing)
	{
		ready = false;
		if (icon.getPosition().x > POS_X)
		{
			icon.move(-10, 0);

		}
		else
		{
			disappearing = false;
			hidden = true;
		}
			
	}
}

void PlayerIcon::draw(sf::RenderWindow& win)
{
	win.draw(icon);
	if(ready)
	{
		win.draw(chat);
		sf::RenderWindow * w = &win;
		text.draw(*w);
	}
}







