#include "GameState.h"

GameState::GameState(gm::gameDataRef data) : data(data)
{

}
GameState::~GameState()
{
	gm::Assets::EraseTexture("TELEPHONE");
	gm::Assets::EraseTexture("KEYBOARD");
	gm::Assets::EraseTexture("MONITOR");
	gm::Assets::EraseTexture("COMPUTER");
	gm::Assets::EraseTexture("DESK");
	gm::Assets::EraseTexture("CUSTOMER_WINDOW");
	gm::Assets::EraseTexture("DRAWER");
	gm::Assets::EraseTexture("CALENDAR");
	gm::Assets::EraseTexture("WALL");
}

void GameState::init()
{
	//Wall
	gm::Assets::LoadTexture("WALL", TEXTURE_WALL);
	if (gm::Assets::getTexture("WALL") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Calendar
	gm::Assets::LoadTexture("CALENDAR", TEXTURE_CALENDAR);
	if (gm::Assets::getTexture("CALENDAR") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Drawer
	gm::Assets::LoadTexture("DRAWER", TEXTURE_DRAWER);
	if (gm::Assets::getTexture("DRAWER") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Customer's window
	gm::Assets::LoadTexture("CUSTOMER_WINDOW", TEXTURE_CUSTOMER_WINDOW);
	if (gm::Assets::getTexture("CUSTOMER_WINDOW") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Desk
	gm::Assets::LoadTexture("DESK", TEXTURE_DESK);
	if (gm::Assets::getTexture("DESK") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Computer
	gm::Assets::LoadTexture("COMPUTER", TEXTURE_COMPUTER);
	if (gm::Assets::getTexture("COMPUTER") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Monitor
	gm::Assets::LoadTexture("MONITOR", TEXTURE_MONITOR);
	if (gm::Assets::getTexture("MONITOR") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Keyboard
	gm::Assets::LoadTexture("KEYBOARD", TEXTURE_KEYBOARD);
	if (gm::Assets::getTexture("KEYBOARD") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}
	//Telephone
	gm::Assets::LoadTexture("TELEPHONE", TEXTURE_TELEPHONE);
	if (gm::Assets::getTexture("TELEPHONE") == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}

	/*Starting settings*/
	//...
}

void GameState::handleInput()
{
	while (gm::Core::getWindow().isOpen())
	{
		/*Events*/
		gm::Core::resetEvent();

		while (gm::Core::getWindow().pollEvent(gm::Core::getEvent()))
		{
			switch (gm::Core::getEvent().type)
			{
			case sf::Event::Closed:
				gm::Core::getWindow().close();
				break;
			case sf::Event::TextEntered:
				gm::Core::setEnteredChar(gm::Core::getEvent().text.unicode);
				break;
			}
		}
	}
}

void GameState::update(sf::RenderWindow &win)
{
	//calendra->update();
	//computer->update();
	//monitor->update();
	//telephone->update();
}

void GameState::draw(sf::RenderWindow& win)
{
	win.clear();

	win.draw(wall);
	//win.draw(calendar);
	win.draw(drawer);
	win.draw(customer_window);
	win.draw(desk);
	//win.draw(computer);
	//win.draw(monitor);
	win.draw(keyboard);
	//win.draw(telephone);


	win.display();
}