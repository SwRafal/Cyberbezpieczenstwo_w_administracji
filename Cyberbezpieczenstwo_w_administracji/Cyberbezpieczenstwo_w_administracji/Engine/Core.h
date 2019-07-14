#pragma once
#include <SFML/Graphics.hpp>

namespace gm
{
	class Core
	{
	public:
		/*Editable constants*/
		const std::string window_name = "Binaryzacja i progowanie obrazow";
		const unsigned int resolution_x = 1200;
		const unsigned int resolution_y = 720;
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
		static void resetEvent() { delete getSingleton().ev; getSingleton().ev = new sf::Event; }
		static sf::VideoMode &getWindowResolution() { return getSingleton().resolution; }
	};
}