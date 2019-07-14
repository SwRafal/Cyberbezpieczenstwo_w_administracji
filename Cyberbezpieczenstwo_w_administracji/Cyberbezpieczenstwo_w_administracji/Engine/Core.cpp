#include "Core.h"

namespace gm
{
	Core::Core()
	{
		resolution.width = resolution_x;
		resolution.height = resolution_y;

		clk.restart();

		window = new sf::RenderWindow(resolution, window_name);
		ev = new sf::Event;
		window->setFramerateLimit(120);

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