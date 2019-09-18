#pragma once

#include "Engine/Engine.h"



namespace gm
{
	/*Put data that will be passed between slideFrames here*/
	struct gameData
	{
		StateMachine machine;

		bool returnToMenu = false;
		bool moveToSave = false;

		int characterChoice = 0;

		sf::String name = "";
		sf::String login = "Admin";
		sf::String password ="Admin";

		sf::String whyFired = " ";
		sf::String knowledge = " ";

		bool sms_sent = false;

		int nagany = 0;

		int day = 0;
	};

	typedef std::shared_ptr<gameData> gameDataRef;

	class Game
	{

		gameDataRef data = std::make_shared<gameData>();
		void run();

	public:
		Game();
		~Game();
	};

}
