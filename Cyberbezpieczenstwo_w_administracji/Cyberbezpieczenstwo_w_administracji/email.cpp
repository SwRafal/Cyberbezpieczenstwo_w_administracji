#include "email.h"

mail::mail() : content(*gm::Assets::getFont())
{
	/* mail */
	gm::Assets::LoadTexture("emailTemplate", TEXTURE_EMAIL_TEMPLATE);
	if (gm::Assets::getTexture("emailTemplate") == nullptr)
		error_win_close();
	email.setTexture(*gm::Assets::getTexture("emailTemplate"));
	email.setPosition(EMAIL_POS_X,EMAIL_POS_Y);

	/* exit button */
	gm::Assets::LoadTexture("exitEmail", TEXTURE_EMAIL_EXIT_BUTTON);
	if (gm::Assets::getTexture("exitEmail") == nullptr)
		error_win_close();

	emailExit.setSize(EMAIL_EXIT_BUTTON_SIZE, EMAIL_EXIT_BUTTON_SIZE);
	emailExit.setPosition(EMAIL_EXIT_BUTTON_POS_X - 52,EMAIL_EXIT_BUTTON_POS_Y + 52);
	emailExit.setTexture(gm::Assets::getTexture("exitEmail"));
	
	/* title */
	title.setFont(*gm::Assets::getFont());
	title.setCharacterSize(20);
	title.setStyle(sf::Text::Style::Regular);
	title.setFillColor(sf::Color::Black);
	title.setString(L"Tytu³");
	title.setPosition(EMAIL_POS_X + 58 - 52, EMAIL_POS_Y + 115 - 52);

	/* sender */
	sender.setFont(*gm::Assets::getFont());
	sender.setCharacterSize(20);
	sender.setStyle(sf::Text::Style::Regular);
	sender.setFillColor(sf::Color::Black);
	sender.setString(L"Nadawca");
	sender.setPosition(EMAIL_POS_X + 58 - 52, EMAIL_POS_Y + 166 - 52);

	/* content */
	content.setSize(685,326);
	content.setPosition(EMAIL_POS_X + 58 - 52, EMAIL_POS_Y + 217 - 52);
	content.setTextSize(18);
	content.setTextColor(sf::Color::Black);
	content.setFillColor(sf::Color::Transparent);
	content.setTextString(L"Treœæ maila");

	/* variables */
	buttonActive = true;
}

void mail::draw(sf::RenderWindow& win)
{
	win.draw(email);
	win.draw(title);
	win.draw(sender);
	content.draw(win);
	win.draw((sf::RectangleShape)emailExit);
}

void mail::newMail(sf::String title, sf::String sender, sf::String content)
{
	this->title.setString(title);
	this->sender.setString(sender);
	this->content.setTextString(content);
}

void mail::setMailButtonActive()
{
	buttonActive = true;
}

void mail::setMailButtonInactive()
{
	buttonActive = false;
}


