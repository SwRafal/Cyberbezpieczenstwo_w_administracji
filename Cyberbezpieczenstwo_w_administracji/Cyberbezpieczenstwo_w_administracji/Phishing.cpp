#include "Phishing.h"

Phishing::Phishing()
{
	turned_on = false;
	show_content = false;
	good_mail = false;

	randomize_time = 0;

	gm::Assets::LoadTexture("PHISHING", TEXTURE_PHISHING);
	if (gm::Assets::getTexture("PHISHING") == nullptr)
		error_win_close();
	else
	{
		background.setTexture(*gm::Assets::getTexture("PHISHING"));
		background.setPosition(200,60);
	}

	if (gm::Assets::getTexture("frame") == nullptr)
	{
		gm::Assets::LoadTexture("frame", PC_SCREEN_FRAME);

		if (gm::Assets::getTexture("frame") == nullptr)
		{
			error_win_close();
		}
	}
	else
	{
		screen.setTexture(*gm::Assets::getTexture("frame"));
		screen.setPosition(177, 17);
	}

	accept = new gm::TextButton(*gm::Assets::getFont());
	accept->setIdleColor(sf::Color(0, 200, 0));
	accept->setAimedColor(sf::Color(0, 250, 0));
	accept->setPressColor(sf::Color(0, 150, 0));
	accept->setTextIdleColor(sf::Color(240,240,240));
	accept->setTextAimedColor(sf::Color(255,255,255));
	accept->setTextPressColor(sf::Color(230,230,230));
	accept->setOutlineThickness(1);
	accept->setOutlineColor(sf::Color::Black);
	accept->setPosition(400,500);
	accept->setSize(110, 50);
	accept->setTextSize(24);
	accept->setTextString(L"Akceptuj");

	decline = new gm::TextButton(*gm::Assets::getFont());
	decline->setIdleColor(sf::Color(200, 0, 0));
	decline->setAimedColor(sf::Color(250, 0, 0));
	decline->setPressColor(sf::Color(150, 0, 0));
	decline->setTextIdleColor(sf::Color(240, 240, 240));
	decline->setTextAimedColor(sf::Color(255, 255, 255));
	decline->setTextPressColor(sf::Color(230, 230, 230));
	decline->setOutlineThickness(1);
	decline->setOutlineColor(sf::Color::Black);
	decline->setPosition(650, 500);
	decline->setSize(110, 50);
	decline->setTextSize(24);
	decline->setTextString(L"Odrzuæ");

	content = new gm::Information(*gm::Assets::getFont());
	content->setSize(600, 350);
	content->setPosition(300, 180);
	content->setOutlineThickness(2);
	content->setOutlineColor(sf::Color::Black);
	content->setFillColor(sf::Color(245, 245, 245));
	content->setTextColor(sf::Color::Black);
	content->setTextSize(24);
	content->setTextString("NULL");
}

Phishing::~Phishing()
{
	gm::Assets::EraseTexture("PHISHING");
	delete accept;
	accept = nullptr;
	delete decline;
	decline = nullptr;
	delete content;
	content = nullptr;
}

void Phishing::draw(sf::RenderWindow &win)
{
	win.draw(background);
	win.draw(screen);

	for (auto &i : mails)
	{
		win.draw(*i);
	}

	if (show_content)
	{
		content->draw(win);

		win.draw(*accept);
		win.draw(*decline);
	}
}

void Phishing::update(sf::RenderWindow &win)
{
	if (randomize_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
	{
		mails.push_back(new gm::TextButton(*gm::Assets::getFont(), sf::Vector2f(600, 400), sf::Vector2f(400, 50), 24, "Random"));

		randomize_time += 2000;
	}

	if (show_content)
	{
		if (accept->clicked(win))
		{
			if (good_mail)
				show_content = false;
			else
				/*lose*/;
		}
		else if (decline->clicked(win))
		{
			if (!good_mail)
				show_content = false;
			else
				/*lose*/;
		}
	}
	else
	{
		for (auto &i : mails)
		{
			if (i->clicked(win))
			{
				content->setTextString(" Od:" /*+ mail*/ + '\n');
				content->setTextString(content->getTextString() + " Tytu³: " /*+ title*/ + '\n');
				content->setTextString("Tresc");

				show_content = true;
			}
		}
	}

	if (mails.size() > 5)
		/*lose*/;
}