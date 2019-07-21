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
		error_win_close();
	else
	{
		wall.setTexture(*gm::Assets::getTexture("WALL"));
		wall.setPosition(sf::Vector2f(0, 0));
	}

	//Calendar
	gm::Assets::LoadTexture("CALENDAR", TEXTURE_CALENDAR);
	if (gm::Assets::getTexture("CALENDAR") == nullptr)
		error_win_close();
	else
	{
		//...
	}

	//Drawer
	gm::Assets::LoadTexture("DRAWER", TEXTURE_DRAWER);
	if (gm::Assets::getTexture("DRAWER") == nullptr)
		error_win_close();
	else
	{
		drawer.setTexture(*gm::Assets::getTexture("DRAWER"));
		drawer.setPosition(sf::Vector2f(SCREEN_WIDTH/2, 100));
	}

	//Customer's window
	gm::Assets::LoadTexture("CUSTOMER_WINDOW", TEXTURE_CUSTOMER_WINDOW);
	if (gm::Assets::getTexture("CUSTOMER_WINDOW") == nullptr)
		error_win_close();
	else
	{
		customer_window.setTexture(*gm::Assets::getTexture("CUSTOMER_WINDOW"));
		customer_window.setPosition(sf::Vector2f(0, 0));
	}

	//Desk
	gm::Assets::LoadTexture("DESK", TEXTURE_DESK);
	if (gm::Assets::getTexture("DESK") == nullptr)
		error_win_close();
	else
	{
		desk.setTexture(*gm::Assets::getTexture("DESK"));
		desk.setPosition(sf::Vector2f(0, SCREEN_HEIGHT/2));
	}

	//Computer
	//gm::Assets::LoadTexture("COMPUTER", TEXTURE_COMPUTER);
	//if (gm::Assets::getTexture("COMPUTER") == nullptr)
		//error_win_close();

	//Monitor
	//gm::Assets::LoadTexture("MONITOR", TEXTURE_MONITOR);
	//if (gm::Assets::getTexture("MONITOR") == nullptr)
		//error_win_close();

	//Keyboard
	//gm::Assets::LoadTexture("KEYBOARD", TEXTURE_KEYBOARD);
	//if (gm::Assets::getTexture("KEYBOARD") == nullptr)
		//error_win_close();

	//Telephone
	//gm::Assets::LoadTexture("TELEPHONE", TEXTURE_TELEPHONE);
	//if (gm::Assets::getTexture("TELEPHONE") == nullptr)
		//error_win_close();


	/*Starting settings*/
	//...
}

void GameState::handleInput()
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

void GameState::update(sf::RenderWindow &win)
{
	//calendra->update();
	//computer->update();
	//monitor->update();
	//telephone->update();
}

void GameState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);

	win.draw(wall);
	//win.draw(calendar);
	win.draw(drawer);
	win.draw(customer_window);
	win.draw(desk);
	//win.draw(computer);
	//win.draw(monitor);
	//win.draw(keyboard);
	//win.draw(telephone);


	win.display();
}