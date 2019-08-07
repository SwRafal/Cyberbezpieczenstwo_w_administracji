#include "IntroState.h"
#include "GameState.h"


IntroState::IntroState(gm::gameDataRef data) : data(data), message(INTRO_TEXT_1,gm::Assets::getFont()), space(INTRO_TEXT_SPACE,gm::Assets::getFont()),
choice1(*gm::Assets::getFont()),choice2(*gm::Assets::getFont()),choice3(*gm::Assets::getFont()),
player1(*gm::Assets::getFont()), player2(*gm::Assets::getFont()), player3(*gm::Assets::getFont())
{
	std::cout << "konstruktor sie skonczyl" << std::endl;
}


IntroState::~IntroState()
{
}

void IntroState::init()
{
	
	state = 0;
	initialized = false;
	nextState = false;

	title.setFillColor(sf::Color::White);
	title.setFont(*gm::Assets::getFont());
	title.setCharacterSize(50);
	title.setStyle(sf::Text::Style::Bold);
	title.setString(L"Cyberbezpieczeñstwo w administracji");
	title.setPosition(SCREEN_WIDTH / 2 - title.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.3);

	//choice buttons

	choice1.setPosition(SCREEN_WIDTH * 0.2,SCREEN_HEIGHT * 0.75);
	choice1.setTextIdleColor(sf::Color::White);
	choice1.setTextAimedColor(sf::Color(230, 120, 255,255));
	choice1.setTextPressColor(sf::Color(216, 46, 255,255));
	choice1.setIdleColor(sf::Color::Transparent);
	choice1.setAimedColor(sf::Color::Transparent);
	choice1.setPressColor(sf::Color::Transparent);
	choice1.setSize(200,55);
	choice1.setTextSize(250);
	choice1.setTextString(L"Bezpieczeñstwo");

	choice2.setPosition(SCREEN_WIDTH * 0.65,SCREEN_HEIGHT * 0.75);
	choice2.setTextIdleColor(sf::Color::White);
	choice2.setTextAimedColor(sf::Color(230, 120, 255,255));
	choice2.setTextPressColor(sf::Color(216, 46, 255,255));
	choice2.setIdleColor(sf::Color::Transparent);
	choice2.setAimedColor(sf::Color::Transparent);
	choice2.setPressColor(sf::Color::Transparent);
	choice2.setSize(200,55);
	choice2.setTextSize(250);
	choice2.setTextString(L"¯ycie na krawêdzi");

	space.setPosition(SCREEN_WIDTH/2 - space.getGlobalBounds().width/2, SCREEN_HEIGHT - (space.getGlobalBounds().height * 2));


	/*playerChoice.setFillColor(sf::Color::White);
	playerChoice.setFont(*gm::Assets::getFont());
	playerChoice.setCharacterSize(50);
	playerChoice.setStyle(sf::Text::Style::Bold);
	playerChoice.setString(L"Wybierz swojego gracza:");
	playerChoice.setPosition(SCREEN_WIDTH / 2 - title.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.3);*/

	//players buttons
	player1.setPosition(SCREEN_WIDTH - player1.getGlobalBounds().width * 6, SCREEN_HEIGHT * 0.75);
	player1.setTextIdleColor(sf::Color::White);
	player1.setTextAimedColor(sf::Color(230, 120, 255, 255));
	player1.setTextPressColor(sf::Color(216, 46, 255, 255));
	player1.setIdleColor(sf::Color::Transparent);
	player1.setAimedColor(sf::Color::Transparent);
	player1.setPressColor(sf::Color::Transparent);
	player1.setSize(200, 55);
	player1.setTextSize(150);
	player1.setTextString("Haker");

	player2.setPosition(SCREEN_WIDTH / 2 - player2.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.75);
	player2.setTextIdleColor(sf::Color::White);
	player2.setTextAimedColor(sf::Color(230, 120, 255, 255));
	player2.setTextPressColor(sf::Color(216, 46, 255, 255));
	player2.setIdleColor(sf::Color::Transparent);
	player2.setAimedColor(sf::Color::Transparent);
	player2.setPressColor(sf::Color::Transparent);
	player2.setSize(200, 55);
	player2.setTextSize(250);
	player2.setTextString("Mag");

	player3.setPosition(SCREEN_WIDTH - player3.getGlobalBounds().width * 2, SCREEN_HEIGHT * 0.75);
	player3.setTextIdleColor(sf::Color::White);
	player3.setTextAimedColor(sf::Color(230, 120, 255, 255));
	player3.setTextPressColor(sf::Color(216, 46, 255, 255));
	player3.setIdleColor(sf::Color::Transparent);
	player3.setAimedColor(sf::Color::Transparent);
	player3.setPressColor(sf::Color::Transparent);
	player3.setSize(300, 55);
	player3.setTextSize(250);
	player3.setTextString("Pani Halina");

	//sound

	gm::Assets::LoadSound("click", CLICK_SOUND_FILEPATH);
	click.setBuffer(*gm::Assets::getSound("click"));

	

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

		

	if(gm::Core::getEnteredChar() == 0x00000020 && (state == 0 || state == 1))
	{
		nextState = true;
	}
}

void IntroState::update(sf::RenderWindow& win)
{
	
	/* Initialize state */
	if(!initialized)
	{
		if(state == 0)
		{
			//already initialized
		}

		if(state == 1)
		{
			message.loadNewText(INTRO_TEXT_2);
			message.setCharacterSize(30);
		}

		if(state == 2)
		{
			message.loadNewText(INTRO_TEXT_CHOICE);
			message.setCharacterSize(60);
		}

		if (state == 3)
		{
			message.loadNewText(INTRO_TEXT_3);
			message.setStyle(sf::Text::Style::Bold);
			message.setCharacterSize(40);
		}

		initialized = true;
	}
	


	if(state == 0)
	{
		message.setPosition(SCREEN_WIDTH / 2 - message.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT * 0.2));
	}
	if(state == 1)
	{
		message.setPosition(SCREEN_WIDTH / 2 - message.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.3);
		space.setPosition(SCREEN_WIDTH/2 - space.getGlobalBounds().width/2, SCREEN_HEIGHT - (space.getGlobalBounds().height * 2));
	}
	if (state == 2)
	{
		message.setPosition(SCREEN_WIDTH / 2 - message.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.1);
		space.setPosition(SCREEN_WIDTH / 2 - space.getGlobalBounds().width / 2, SCREEN_HEIGHT - (space.getGlobalBounds().height * 2));
	}
	if(state == 3)
	{
		message.setPosition(SCREEN_WIDTH / 2 - message.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.3);
		if(message.getString().getSize() == 14)
		{
			message.setString(message.getString().substring(0,13));
			message.setString(message.getString() + "?");
		}
	}
	
	
	message.updateText();
	space.updateText();

	if (player1.clicked(gm::Core::getWindow()))
	{
		click.play();
		Sleep(100);
		nextState = true;
		MessageBoxA(NULL, "Welcome to THE GAME, Haker...", "Hacker", MB_OK | MB_ICONEXCLAMATION);
		data->machine.addState(gm::StateRef(new GameState(this->data)));
	}
	if (player2.clicked(gm::Core::getWindow()))
	{
		click.play();
		Sleep(100);
		nextState = true;
		MessageBoxA(NULL, "Welcome to the MYSTERIOUS world, Mag...", "Mag", MB_OK | MB_ICONEXCLAMATION);
		data->machine.addState(gm::StateRef(new GameState(this->data)));
	}
	if (player3.clicked(gm::Core::getWindow()))
	{
		click.play();
		Sleep(100);
		nextState = true;
		MessageBoxA(NULL, "Witaj w Grze, Gra¿ynko...\nznaczy Halinko...", "Pani Halina", MB_OK | MB_ICONEXCLAMATION);
		data->machine.addState(gm::StateRef(new GameState(this->data)));
	}
	if(choice1.clicked(gm::Core::getWindow()))
	{
		click.play();
		Sleep(100);
		nextState = true;
		MessageBoxA(NULL, "WORK IN PROGRESS", "HI", MB_OK | MB_ICONEXCLAMATION);
		data->machine.addState(gm::StateRef(new GameState (this->data)));
	}
	if(choice2.clicked(gm::Core::getWindow()))
	{
		click.play();
		Sleep(100);
		nextState = true;
		MessageBoxA(NULL, "WORK IN PROGRESS", "HELLO", MB_OK | MB_ICONEXCLAMATION);
		data->machine.addState(gm::StateRef(new GameState (this->data)));
	}


	if(nextState)
	{
		state++;
		nextState = false;
		initialized = false;

	}

}

void IntroState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);

	if(state == 0)
		win.draw(title);
	if(state == 1 )
		win.draw(space);

	
	if (state == 2)
	{
		win.draw(player1);
		win.draw(player2);
		win.draw(player3);
	}

	if(state == 3)
	{
		win.draw(choice1);
		win.draw(choice2);
	}

	win.draw(message);
	
	
	win.display();
}

