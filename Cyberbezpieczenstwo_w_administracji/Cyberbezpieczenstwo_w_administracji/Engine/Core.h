#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Definitions.h"

namespace gm
{
	class Core
	{
	public:
		/*Editable constants*/
		const std::string window_name = SCREEN_TITLE;
		const unsigned int resolution_x = SCREEN_WIDTH;
		const unsigned int resolution_y = SCREEN_HEIGHT;
		const unsigned int fps = FPS;
		//////////////////////////////////////////////////////////////////
	private:
		Core();
		static Core &getSingleton()
		{
			static Core singleton;
			return singleton;
		}

		sf::RenderWindow *window = nullptr;
		sf::Event *ev = nullptr;
		sf::Uint32 last_entered_char;
		sf::Clock clk;
		sf::VideoMode resolution;
	public:
		~Core();

		static sf::Clock& getClock() { return getSingleton().clk; }
		static sf::RenderWindow &getWindow() { return *(getSingleton().window); }
		static sf::Event &getEvent() { return *(getSingleton().ev); }
		static sf::VideoMode &getWindowResolution() { return getSingleton().resolution; }

		static void setEnteredChar(sf::Uint32 key) { getSingleton().last_entered_char = key; }
		static sf::Uint32 getEnteredChar() { return getSingleton().last_entered_char; }
		static void resetEvent() { delete getSingleton().ev; getSingleton().ev = new sf::Event; }
	};
}