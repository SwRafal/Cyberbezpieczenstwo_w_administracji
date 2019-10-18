#pragma once
#include "TextButton.h"
#include <iostream>

#define FRAME_BREAK 30
#define BACKSPACE 8
#define ENTER 13

namespace gm
{
	class TextField : public TextButton
	{
	private:
		bool is_active = false;
		bool hasLimit = true;
		unsigned short limit;

		bool cursor_visible = false;
		sf::RectangleShape cursor;
		unsigned int frame_br;
	public:
		void setActive(bool active);
		void switchStatus();
		void setLimit(bool on, unsigned short limit);
		void setLimit(bool on);

		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void update(sf::RenderWindow &win, sf::Uint32 char_entered);

		TextField(sf::Font &font) : TextField(font, sf::Vector2f(0, 0), sf::Vector2f(200, 100)) {};
		TextField(sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, unsigned int font_size = 32);
		TextField(const TextField &field) : TextButton(field) {};
		~TextField();

		bool isActive() { return is_active; }
	};
}