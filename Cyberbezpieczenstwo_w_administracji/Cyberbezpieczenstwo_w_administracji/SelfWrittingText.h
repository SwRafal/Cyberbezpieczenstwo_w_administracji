#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Windows.h"
#include <queue>
#include <locale>
#include <iostream>


namespace gm
{
	class SelfWrittingText : public sf::Text
	{
	private:
		std::queue<wchar_t> text_queue;
	public:
		SelfWrittingText(std::string fileName, sf::Font* font);
		~SelfWrittingText() {} ;
		
		void updateText();
		void setTextProperties(sf::Font* font, int characterSize, sf::Color textColor,sf::Text::Style textStyle,int posX,int posY);

	};
}
