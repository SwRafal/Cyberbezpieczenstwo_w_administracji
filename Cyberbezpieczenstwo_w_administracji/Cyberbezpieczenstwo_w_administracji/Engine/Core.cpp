#include "Core.h"

namespace gm
{
	Core::Core()
	{
		resolution.width = resolution_x;
		resolution.height = resolution_y;

		clk.restart();

		window = new sf::RenderWindow(resolution, window_name,sf::Style::Close);
		ev = new sf::Event;
		window->setFramerateLimit(fps);

		//window->setIcon();
	}

	Core::~Core()
	{
		delete window;
		window = nullptr;
		delete ev;
		ev = nullptr;
	}
}