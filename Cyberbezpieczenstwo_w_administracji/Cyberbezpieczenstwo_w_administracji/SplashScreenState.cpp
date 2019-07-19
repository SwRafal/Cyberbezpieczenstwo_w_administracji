#include "SplashScreenState.h"



SplashScreenState::SplashScreenState(gm::gameDataRef data) : data(data)
{

}


SplashScreenState::~SplashScreenState()
{
}

void SplashScreenState::init()
{
	
}

void SplashScreenState::handleInput()
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

void SplashScreenState::update(sf::RenderWindow &win)
{
	
}

void SplashScreenState::draw(sf::RenderWindow& win)
{
	win.clear();

	

	win.display();
}
