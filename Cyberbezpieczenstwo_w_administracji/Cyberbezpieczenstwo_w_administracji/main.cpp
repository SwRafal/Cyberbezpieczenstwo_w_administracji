#include <iostream>
#include "Engine/Engine.h"

#define ICON_FILEPATH "icon.png"
#define ICON_SIZE 32
#define FONT_FILEPATH "fonts/default.ttf"

int main()
{
	srand(time(nullptr));

	/*Preparing window*/
	gm::Assets::LoadIcon(ICON_FILEPATH);
	if (gm::Assets::getIcon() != nullptr)
		gm::Core::getWindow().setIcon(ICON_SIZE, ICON_SIZE, gm::Assets::getIcon()->getPixelsPtr());

	/*Loading font*/
	gm::Assets::LoadFont(FONT_FILEPATH);
	if (gm::Assets::getFont() == nullptr)
	{
		system("pause");
		exit(EXIT_FAILURE);
	}


	/*Window loop*/
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

		/*Display graphics*/
		gm::Core::getWindow().clear(sf::Color::Black);
		gm::Core::getWindow().display();
	}

	return EXIT_SUCCESS;
}