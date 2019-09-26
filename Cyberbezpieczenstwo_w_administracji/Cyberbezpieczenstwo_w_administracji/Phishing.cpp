#include "Phishing.h"

Phishing::Phishing()
{
	turned_on = false;
	show_content = false;
	good_mail = false;
	game_lost = false;
	which_mail = 0;

	randomize_time = 0;

	points = 0;
	text_points.setFont(*gm::Assets::getFont());
	text_points.setFillColor(sf::Color::Blue);
	text_points.setOutlineThickness(1);
	text_points.setOutlineColor(sf::Color::White);
	text_points.setCharacterSize(48);
	text_points.setPosition(20, 1);

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
	accept->setPosition(400,600);
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
	decline->setPosition(650, 600);
	decline->setSize(110, 50);
	decline->setTextSize(24);
	decline->setTextString(L"Odrzuæ");

	content = new gm::Information(*gm::Assets::getFont());
	content->setSize(600, 350);
	content->setPosition(300, 250);
	content->setOutlineThickness(2);
	content->setOutlineColor(sf::Color::Black);
	content->setFillColor(sf::Color(245, 245, 245));
	content->setTextColor(sf::Color::Black);
	content->setTextSize(16);
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

	win.draw(screen);

	win.draw(text_points);
}

void Phishing::update(sf::RenderWindow &win)
{
	if (game_lost)
	{
		show_content = false;

		sf::Vector2f new_points_pos;
		new_points_pos.x = SCREEN_WIDTH / 2 - (text_points.getLocalBounds().left + text_points.getLocalBounds().width) / 2;
		new_points_pos.y = SCREEN_HEIGHT / 2 - (text_points.getLocalBounds().top + text_points.getLocalBounds().height) / 2;
		text_points.setPosition(new_points_pos);

		while (!mails.empty())
			mails.pop_back();

		if (background.getColor() == sf::Color(255, 0, 0))
			turned_on = false;

		background.setColor(sf::Color(255, background.getColor().g - 1, background.getColor().b - 1));
	}
	else
	{
		if (randomize_time < gm::Core::getClock().getElapsedTime().asMilliseconds())
		{
			PhishingMail* new_mail = new PhishingMail(*gm::Assets::getFont(), sf::Vector2f(MAIL_POS_X, MAIL_POS_Y + mails.size() * MAIL_HEIGHT), sf::Vector2f(MAIL_WIDTH, MAIL_HEIGHT), 20, "Random");
			new_mail->setIdleColor(sf::Color(250, 250, 250));
			new_mail->setAimedColor(sf::Color(254,254,254));
			new_mail->setPressColor(sf::Color(230, 230, 230));
			new_mail->setOutlineThickness(-1);
			new_mail->setOutlineColor(sf::Color::Black);
			new_mail->setFillColor(new_mail->getIdleColor());

			//Losu losu
			new_mail->good_mail = rand() % 2;

			if (new_mail->good_mail)
			{
				int randomized = rand() % 14;
				new_mail->sender = g_senders[randomized];
				new_mail->title = g_titles[randomized];
				new_mail->content = g_contents[randomized];
			}
			else
			{
				int randomized = rand() % 20;
				new_mail->sender = b_senders[randomized];
				new_mail->title = b_titles[randomized];
				new_mail->content = b_contents[randomized];
			}

			new_mail->setTextString(new_mail->title);

			mails.push_back(new_mail);

			randomize_time = gm::Core::getClock().getElapsedTime().asMilliseconds() + 2500;
		}

		if (show_content)
		{
			if (accept->clicked(win))
			{
				if (good_mail)
				{
					mails.erase(mails.begin()+which_mail);
					pos_mails();
					show_content = false;
					points += 50;
				}
				else
					game_lost = true;
			}
			else if (decline->clicked(win))
			{
				if (!good_mail)
				{
					mails.erase(mails.begin() + which_mail);
					pos_mails();
					show_content = false;
					points += 50;
				}
				else
					game_lost = true;
			}
		}
		else
		{
			int which = 0;
			for (auto &i : mails)
			{
				if (i->clicked(win))
				{
					good_mail = i->good_mail;
					content->setTextString(" Od:" + i->sender + '\n');
					content->setTextString(content->getTextString() + L" Tytu³: " + i->title + '\n' + ' ' + '\n');
					content->setTextString(content->getTextString() + i->content);

					which_mail = which;
					show_content = true;
				}
				which++;
			}
		}

		if (mails.size() > 7)
			game_lost = true;
	}

	text_points.setString("Punkty: " + std::to_string(points));
}

void Phishing::pos_mails()
{
	int number = 0;
	for (auto &i : mails)
	{
		i->setPosition(MAIL_POS_X, MAIL_POS_Y + number * MAIL_HEIGHT);
		number++;
	}
}