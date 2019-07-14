#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace gm
{
	class Information : public sf::RectangleShape
	{
	private:
		sf::Text text;
		sf::String txt_str;
		void adjust_text();
	public:
		void setRotation(float) = delete;
		void rotate(float) = delete;
		void scale(const sf::Vector2f&) = delete;
		void setScale(const sf::Vector2f&) = delete;
		void scale(float, float) = delete;
		void setScale(float, float) = delete;

		void setSize(const sf::Vector2f & size);
		void setSize(float x, float y);
		void setPosition(const sf::Vector2f &position);
		void setPosition(float x, float y);
		void move(const sf::Vector2f &offset);
		void move(float offsetX, float offsetY);

		//Sam tekst
		void setTextFont(sf::Font& font);
		void setTextColor(sf::Color color);
		void setTextString(sf::String str);
		void setTextSize(unsigned int size);

		//G³ówne
		void draw(sf::RenderWindow &win);

		Information(sf::Font &font) : Information(font, sf::Vector2f(0, 0), sf::Vector2f(200, 100)) {};
		Information(sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, unsigned int font_size = 32);
		Information(const Information &info);
		~Information();

		const sf::Font &getTextFont() { return *(text.getFont()); }
		const sf::Color &getTextColor() { return text.getFillColor(); }
		sf::String getTextString() { return text.getString(); }
		const unsigned int getTextSize() { return text.getCharacterSize(); }
	};
}