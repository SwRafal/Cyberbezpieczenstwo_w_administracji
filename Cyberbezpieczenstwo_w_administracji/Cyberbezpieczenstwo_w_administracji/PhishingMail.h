#pragma once
#include "Engine/TextButton.h"

class PhishingMail : public gm::TextButton
{
public:
	bool good_mail;
	sf::String sender;
	sf::String title;
	sf::String content;

	PhishingMail(sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, unsigned int font_size = 32, const sf::String &str = "Button") 
		: TextButton(font, position, size, font_size, str) 	{}

	void pos_mails();
};