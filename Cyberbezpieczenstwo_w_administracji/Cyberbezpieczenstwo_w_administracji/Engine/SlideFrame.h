#pragma once
#include <SFML/Graphics.hpp>

namespace gm
{
	class SlideFrame
	{
	public:
		virtual void init() = 0;

		virtual void handleInput() = 0;
		virtual void update() = 0;
		virtual void draw(sf::RenderWindow &win) = 0;
		

		virtual ~SlideFrame() {};
	};
}