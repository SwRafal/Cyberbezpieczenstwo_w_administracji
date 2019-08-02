#include "GameState.h"
#include <thread>
#include "MenuState.h"

GameState::GameState(gm::gameDataRef data) : data(data)
{

}
GameState::~GameState()
{
	delete calendar;
	calendar = nullptr;
	delete watch;
	watch = nullptr;
	delete coffee;
	coffee = nullptr;
	delete battery;
	battery = nullptr;
	delete bell;
	bell = nullptr;

	gm::Assets::EraseTexture("BELL");
	gm::Assets::EraseTexture("BATTERY");
	gm::Assets::EraseTexture("COFFEE");
	gm::Assets::EraseTexture("WATCH");
	gm::Assets::EraseTexture("TELEPHONE");
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
		calendar = new Calendar(gm::Assets::getFont(), gm::Assets::getTexture("CALENDAR")/*,date*/);
	}

	//Watch
	gm::Assets::LoadTexture("WATCH", TEXTURE_WATCH);
	if (gm::Assets::getTexture("WATCH") == nullptr)
		error_win_close();
	else
	{
		watch = new Watch(gm::Assets::getFont(), gm::Assets::getTexture("WATCH"), 8, 0);
	}

	//Coffee
	gm::Assets::LoadTexture("COFFEE", TEXTURE_COFFEE);
	if (gm::Assets::getTexture("COFFEE") == nullptr)
		error_win_close();
	else
	{
		coffee = new Coffee(gm::Assets::getTexture("COFFEE"));
	}

	//Battery
	gm::Assets::LoadTexture("BATTERY", TEXTURE_BATTERY);
	if (gm::Assets::getTexture("BATTERY") == nullptr)
		error_win_close();
	else
	{
		battery = new Battery(gm::Assets::getTexture("BATTERY"));
	}

	//Bell
	gm::Assets::LoadTexture("BELL", TEXTURE_BELL);
	if (gm::Assets::getTexture("BELL") == nullptr)
		error_win_close();
	else
	{
		bell = new Bell(gm::Assets::getTexture("BELL"));
	}

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
		gm::Core::setEnteredChar(NULL);
		


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

	if(gm::Core::getEnteredChar() == 0x0000001B)
	{
		//pause state		
		sf::Texture tex;
		tex.create(gm::Core::getWindow().getSize().x,gm::Core::getWindow().getSize().y);
		tex.update(gm::Core::getWindow());
		gm::Assets::LoadTextureFromImage("pause bg", tex.copyToImage());
		data->machine.addState(gm::StateRef(new PauseState (this->data)),false);      
	}
	if(data->returnToMenu == true)
	{
		data->returnToMenu = false;
		data->machine.addState(gm::StateRef(new MenuState (this->data))); 
	}
}

void GameState::update(sf::RenderWindow &win)
{
	calendar->update(win);
	watch->update(gm::Core::getClock());
	//telephone->update();
	if (coffee->update_drunk(win))
	{
		battery->setLevel(battery->getLevel() + 20);
	}
	battery->update_empty(gm::Core::getClock());

	if (bell->update_rung(win))
	{
		//Call the client
	}
}

void GameState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);

	win.draw(wall);
	calendar->draw(win);
	bell->draw(win);
	watch->draw(win);
	//win.draw(telephone);
	coffee->draw(win);
	battery->draw(win);

	win.display();
}