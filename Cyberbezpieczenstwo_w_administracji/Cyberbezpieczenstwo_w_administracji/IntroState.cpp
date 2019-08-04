#include "IntroState.h"




IntroState::IntroState(gm::gameDataRef data) : data(data), message(TEXT_FILE_FILEPATH,gm::Assets::getFont())
{
}


IntroState::~IntroState()
{
}

void IntroState::init()
{
	

}

void IntroState::handleInput()
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
}

void IntroState::update(sf::RenderWindow& win)
{
	
	
	message.updateText();
	
	
	

}

void IntroState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);
	win.draw(message);
	win.display();
}

