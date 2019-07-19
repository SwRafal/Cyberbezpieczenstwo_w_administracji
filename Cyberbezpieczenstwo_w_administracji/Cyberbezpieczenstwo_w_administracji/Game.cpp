#include "Game.h"
#include "Definitions.h"
#include "SplashScreenState.h"



namespace gm
{

	Game::Game()
	{
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

		data->machine.addState(StateRef(new SplashScreenState (this->data)));

		this->run();
	}

	void Game::run()
	{
		/*Game loop*/
		while (gm::Core::getWindow().isOpen())
		{
			//adding or removing slides
			this->data->machine.processStateChanges();

			this->data->machine.getActiveState()->handleInput();
			this->data->machine.getActiveState()->update(Core::getWindow());
			this->data->machine.getActiveState()->draw(Core::getWindow());
		}
	}


	Game::~Game()
	{
	}

}