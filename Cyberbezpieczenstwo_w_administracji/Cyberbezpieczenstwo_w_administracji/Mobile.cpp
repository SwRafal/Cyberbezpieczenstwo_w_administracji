#include "Mobile.h"

/*Maintenance(?)*/

Mobile::Mobile(sf::Texture *tex) : text(*gm::Assets::getFont())
{
	this->setTexture(tex);

	/* set position */

	this->setSize(sf::Vector2f(MOBILE_WIDTH, MOBILE_HEIGHT));
	this->setIdleColor(sf::Color::White);
	this->setAimedColor(sf::Color(190, 200, 190));
	this->setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(MOBILE_POS_X, MOBILE_POS_Y));

	gm::Assets::LoadSound("vibration", MOBILE_VIBRATION_FILEPATH);
	vibration.setBuffer(*gm::Assets::getSound("vibration"));

	mobile_view.setTexture(*gm::Assets::getTexture("MOBILE_VIEW"));
	mobile_view.setPosition(MOBILE_VIEW_POS_X, MOBILE_VIEW_POS_Y);

	text.setSize(MOBILE_VIEW_WIDTH - 100, MOBILE_VIEW_HEIGHT - 100);
	text.setPosition(mobile_view.getPosition().x + 50, mobile_view.getPosition().y + 60);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color::Transparent);
	text.setTextSize(20);

	/* variables */

	calling = false;
	pickedUp = false;
}


Mobile::~Mobile()
{
}


void Mobile::update(sf::RenderWindow& win)
{
	if (calling)
	{
		if (vibration.getStatus() == sf::Sound::Stopped)
			vibration.play();

		if (this->getPosition().x == MOBILE_POS_X)
			this->move(1, 0);
		else
			this->setPosition(MOBILE_POS_X, this->getPosition().y);

		if (this->getPosition().y == MOBILE_POS_Y)
			this->move(0, 1);
		else
			this->setPosition(this->getPosition().x, MOBILE_POS_Y);
	}
	else
		vibration.stop();

	if (clicked(win))
	{
		if (calling)
		{
			pickedUp = true;
		}
		calling = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pickedUp)
	{
			pickedUp = false;
	}

}

void Mobile::draw(sf::RenderWindow& win)
{
	win.draw((sf::RectangleShape)*this);
	if (pickedUp)
	{
		win.draw(mobile_view);
		text.draw(win);
	}
}

void Mobile::draw_view(sf::RenderWindow &win)
{
	win.draw(mobile_view);
	text.draw(win);
}

void Mobile::call()
{
	calling = true;
}