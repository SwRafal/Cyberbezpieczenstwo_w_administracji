#include "Phishing.h"

Phishing::Phishing()
{
	turned_on = false;
	show_content = false;

	gm::Assets::LoadTexture("PHISHING", TEXTURE_PHISHING);
	if (gm::Assets::getTexture("PHISHING") == nullptr)
		error_win_close();
	else
	{
		background.setTexture(*gm::Assets::getTexture("PHISHING"));
		background.setPosition(200,60);
	}

	accept = new gm::TextButton(*gm::Assets::getFont());
	accept->setIdleColor(sf::Color(0, 200, 0));
	accept->setAimedColor(sf::Color(0, 250, 0));
	accept->setPressColor(sf::Color(0, 150, 0));
	accept->setTextIdleColor(sf::Color(240,240,240));
	accept->setTextAimedColor(sf::Color(255,255,255));
	accept->setTextPressColor(sf::Color(230,230,230));
	accept->setPosition(400,500);
	accept->setSize(100, 25);
	accept->setTextString(L"Akceptuj");

	decline = new gm::TextButton(*gm::Assets::getFont());
	decline->setIdleColor(sf::Color(200, 0, 0));
	decline->setAimedColor(sf::Color(250, 0, 0));
	decline->setPressColor(sf::Color(150, 0, 0));
	decline->setTextIdleColor(sf::Color(240, 240, 240));
	decline->setTextAimedColor(sf::Color(255, 255, 255));
	decline->setTextPressColor(sf::Color(230, 230, 230));
	decline->setPosition(400, 500);
	decline->setSize(100, 25);
	decline->setTextString(L"Odrzuæ");
}

Phishing::~Phishing()
{
	gm::Assets::EraseTexture("PHISHING");
	delete accept;
	accept = nullptr;
	delete decline;
	decline = nullptr;
}

void Phishing::draw(sf::RenderWindow &win)
{
	win.draw(background);

	if (show_content)
	{
		win.draw(*accept);
		win.draw(*decline);
	}
}

void Phishing::update(sf::RenderWindow &win)
{

}