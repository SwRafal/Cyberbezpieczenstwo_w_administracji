#include "TextButton.h"
#include <iostream>

namespace gm
{
	//Tekst
	void TextButton::adjust_text()
	{
		std::string str = text.getString();

		text.setString("A");//Chwilowa podmiana na litere 'A' dla lepszego dopasowania wysokoœci
		while (text.getLocalBounds().height > Button::getSize().y)
			text.setCharacterSize(text.getCharacterSize() - 1);

		sf::Vector2f text_pos;
		text_pos.y = Button::getPosition().y + Button::getSize().y / 2.f - (text.getLocalBounds().top + text.getLocalBounds().height / 2.f);

		text.setString(str);

		while (text.getLocalBounds().width > Button::getSize().x)
			text.setCharacterSize(text.getCharacterSize() - 1);

		
		text_pos.x = Button::getPosition().x + Button::getSize().x / 2.f - (text.getLocalBounds().left + text.getLocalBounds().width / 2.f);

		text.setPosition(text_pos);
	}

	void TextButton::setTextSize(unsigned int size)
	{
		if (text.getFont() == nullptr)
		{
			std::cout << "Text button has not a valid font" << std::endl;
			return;
		}

		wanted_char_size = size;
		text.setCharacterSize(wanted_char_size);

		adjust_text();
	}

	void TextButton::setTextFont(const sf::Font& font)
	{
		text.setFont(font);
	}

	void TextButton::setTextIdleColor(const sf::Color &color)
	{
		idle_text_color = color;
	}
	void TextButton::setTextAimedColor(const sf::Color &color)
	{
		aimed_text_color = color;
	}
	void TextButton::setTextPressColor(const sf::Color &color)
	{
		press_text_color = color;
	}

	void TextButton::setTextString(const sf::String &str)
	{
		text.setString(str);
		setTextSize(wanted_char_size);
		adjust_text();
	}

	void TextButton::setTextOutlineThickness(float thickness)
	{
		text.setOutlineThickness(thickness);
	}

	void TextButton::setTextOutlineColor(const sf::Color &color)
	{
		text.setOutlineColor(color);
	}

	//Ogó³
	void TextButton::setSize(const sf::Vector2f &size)
	{
		float previous_size = Button::getSize().y;
		Button::setSize(size);
		setTextSize(size.y/previous_size);
	}

	void TextButton::setSize(float x, float y)
	{
		float previous_size = Button::getSize().y;
		Button::setSize(sf::Vector2f(x,y));
		setTextSize(y / previous_size);
	}

	void TextButton::setPosition(const sf::Vector2f &position)
	{
		Button::setPosition(position);
		sf::Vector2f text_pos;
		text_pos.y = Button::getPosition().y + Button::getSize().y / 2.f - (text.getLocalBounds().top + text.getLocalBounds().height / 2.f);
		text_pos.x = Button::getPosition().x + Button::getSize().x / 2.f - (text.getLocalBounds().left + text.getLocalBounds().width / 2.f);

		text.setPosition(text_pos);
	}

	void TextButton::setPosition(float x, float y)
	{
		Button::setPosition(sf::Vector2f(x, y));
		sf::Vector2f text_pos;
		text_pos.y = Button::getPosition().y + Button::getSize().y / 2.f - (text.getLocalBounds().top + text.getLocalBounds().height / 2.f);
		text_pos.x = Button::getPosition().x + Button::getSize().x / 2.f - (text.getLocalBounds().left + text.getLocalBounds().width / 2.f);

		text.setPosition(text_pos);
	}

	void TextButton::move(const sf::Vector2f &offset)
	{
		Button::move(offset);
		text.move(offset);
	}

	void TextButton::move(float offsetX, float offsetY)
	{
		Button::move(sf::Vector2f(offsetX, offsetY));
		text.move(sf::Vector2f(offsetX, offsetY));
	}

	//G³ówne metody
	void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(sf::RectangleShape(*this));
		target.draw(text);
	}

	bool TextButton::clicked(sf::RenderWindow &win)
	{
		if (win.hasFocus())
		{
			if (isHeld())
				text.setFillColor(press_text_color);
			else if (aimed(win))
				text.setFillColor(aimed_text_color);
			else
				text.setFillColor(idle_text_color);
		}

		if (Button::clicked(win))
			return true;
		else
			return false;
	}

	TextButton::TextButton(sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, unsigned int font_size, const sf::String &str)
		:Button(position, size)
	{
		text.setFont(font);
		text.setString(str);
		text.setFillColor(sf::Color(255, 255, 255));

		wanted_char_size = font_size;
		setTextSize(font_size);
	}

	TextButton::TextButton(const TextButton &textbutton)
		:Button(textbutton)
	{
		text = textbutton.text;
		wanted_char_size = textbutton.wanted_char_size;
	}

	TextButton::~TextButton() {}
}