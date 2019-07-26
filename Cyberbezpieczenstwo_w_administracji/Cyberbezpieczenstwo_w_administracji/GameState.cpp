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
		calendar = new Calendar(gm::Assets::getFont(), gm::Assets::getTexture("CALENDAR"), "as", "df", "milczy");
		calendar->setPosition(CALENDAR_POS_X, CALENDAR_POS_Y);
	}

	//Telephone
	//gm::Assets::LoadTexture("TELEPHONE", TEXTURE_TELEPHONE);
	//if (gm::Assets::getTexture("TELEPHONE") == nullptr)
		//error_win_close();

	//Watch
	gm::Assets::LoadTexture("WATCH", TEXTURE_WATCH);
	if (gm::Assets::getTexture("WATCH") == nullptr)
		error_win_close();
	else
	{
		watch.setTexture(*gm::Assets::getTexture("WATCH"));
		watch.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - gm::Assets::getTexture("WATCH")->getSize().x / 2 , 0));
	}


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
	//calendra->update();
	//telephone->update();
}

void GameState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);

	win.draw(wall);
	calendar->draw(win);
	//win.draw(telephone);
	win.draw(watch);

	win.display();
}