#pragma once
#include "Button.h"

namespace gm
{
	class TextButton : public Button
	{
	private:
		sf::Text text;
		unsigned int wanted_char_size;
		void adjust_text();

		sf::Color idle_text_color;
		sf::Color aimed_text_color;
		sf::Color press_text_color;
	public:
		//Ca³oœæ guzika
		void setSize(const sf::Vector2f &size);
		void setSize(float x, float y);
		void setPosition(const sf::Vector2f &position);
		void setPosition(float x, float y);
		void move(const sf::Vector2f &offset);
		void move(float offsetX, float offsetY);

		//Sam tekst
		void setTextFont(const sf::Font& font);
		void setTextString(const sf::String &str);
		void setTextSize(unsigned int size);
		void setTextOutlineThickness(float thickness);
		void setTextOutlineColor(const sf::Color &color);

		void setTextIdleColor(const sf::Color &color);
		void setTextAimedColor(const sf::Color &color);
		void setTextPressColor(const sf::Color &color);

		//G³ówne
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		bool clicked(sf::RenderWindow &win);

		TextButton(sf::Font &font) : TextButton(font, sf::Vector2f(0, 0), sf::Vector2f(200, 100)) {};
		TextButton(sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, unsigned int font_size=32, const sf::String &str = "Button");
		TextButton(const TextButton &button);
		~TextButton();

		const sf::Font *getTextFont() { return text.getFont(); }
		const sf::Color &getTextColor() { return text.getFillColor(); }
		const sf::String &getTextString() { return text.getString(); }
		unsigned int getTextSize() { return text.getCharacterSize(); }
		float getTextOutlineThickness() { return text.getOutlineThickness(); }
		const sf::Color &getTextOutlineColor() { return text.getOutlineColor(); }

		const sf::Color &getTextIdleColor() { return idle_text_color; }
		const sf::Color &getTextAimedColor() { return aimed_text_color; }
		const sf::Color &getTextPressColor() { return press_text_color; }
	};
}