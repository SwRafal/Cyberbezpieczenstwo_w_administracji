#pragma once
#include <SFML/Graphics.hpp>

namespace bu
{
	/*Consts for selecting between main_menu, game, options etc.*/
	enum SECTIONS
	{
		NO_SECTION = 0,
		MAIN_MENU = 1
		//...add more here if needed...
	};

	class SlideFrame
	{
	public:
		virtual void init() = 0;

		virtual void draw(sf::RenderWindow &win) = 0;
		virtual bu::SECTIONS update(sf::RenderWindow &win) = 0;

		virtual ~SlideFrame() {};
	};
}