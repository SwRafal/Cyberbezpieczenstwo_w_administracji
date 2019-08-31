#include "IntroState.h"
#include "GameState.h"


IntroState::IntroState(gm::gameDataRef data) : data(data), message(INTRO_TEXT_1,gm::Assets::getFont()), space(INTRO_TEXT_SPACE,gm::Assets::getFont()),
choice1(*gm::Assets::getFont()),choice2(*gm::Assets::getFont()),choice3(*gm::Assets::getFont()), message2(INTRO_TEXT_6,gm::Assets::getFont())
{
	std::cout << "konstruktor" << std::endl;
}


IntroState::~IntroState()
{
}

void IntroState::init()
{
	std::cout << "10" << std::endl;
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
	std::cout << "11" << std::endl;
	choice1.setTextIdleColor(sf::Color::White);
	choice1.setTextAimedColor(sf::Color(230, 120, 255,255));
	choice1.setTextPressColor(sf::Color(216, 46, 255,255));
	choice1.setIdleColor(sf::Color::Transparent);
	choice1.setAimedColor(sf::Color::Transparent);
	choice1.setPressColor(sf::Color::Transparent);
	choice1.setPosition(SCREEN_WIDTH * 0.2,SCREEN_HEIGHT * 0.75);

	choice1.setSize(200,55);
	choice1.setTextSize(250);
	choice1.setTextString(L"Bezpieczeñstwo");

	choice2.setTextIdleColor(sf::Color::White);
	choice2.setTextAimedColor(sf::Color(230, 120, 255,255));
	choice2.setTextPressColor(sf::Color(216, 46, 255,255));
	choice2.setIdleColor(sf::Color::Transparent);
	choice2.setAimedColor(sf::Color::Transparent);
	choice2.setPressColor(sf::Color::Transparent);

	choice2.setPosition(SCREEN_WIDTH * 0.65,SCREEN_HEIGHT * 0.75);
	choice2.setSize(200,55);
	choice2.setTextSize(250);
	choice2.setTextString(L"¯ycie na krawêdzi");

	choice3.setTextIdleColor(sf::Color::White);
	choice3.setTextAimedColor(sf::Color(230, 120, 255,255));
	choice3.setTextPressColor(sf::Color(216, 46, 255,255));
	choice3.setIdleColor(sf::Color::Transparent);
	choice3.setAimedColor(sf::Color::Transparent);
	choice3.setPressColor(sf::Color::Transparent);

	choice3.setPosition(SCREEN_WIDTH * 0.65,SCREEN_HEIGHT * 0.75);
	choice3.setSize(200,55);
	choice3.setTextSize(250);

	space.setPosition(SCREEN_WIDTH/2 - space.getGlobalBounds().width/2, SCREEN_HEIGHT - (space.getGlobalBounds().height * 2));

	std::cout << "12" << std::endl;
	//sound
	gm::Assets::LoadSound("click", CLICK_SOUND_FILEPATH);
	click.setBuffer(*gm::Assets::getSound("click"));

	delay = true;
	std::cout << "14" << std::endl;
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

		std::cout << "15" << std::endl;

	if(gm::Core::getEnteredChar() == 0x00000020 && (state == 0 || state == 1))
	{
		nextState = true;
	}
	if(gm::Core::getEnteredChar() == 0x00000020 && state == 5)
	{
		//MessageBoxA(NULL, "WORK IN PROGRESS", "HELLO", MB_OK | MB_ICONEXCLAMATION);
		data->machine.addState(gm::StateRef(new GameState (this->data)));
	}
}

void IntroState::update(sf::RenderWindow& win)
{
	std::cout << "16" << std::endl;
	/* Initialize state */
	if(!initialized)
	{
		if(state == 0) //tytul
		{
			//already initialized
			choice1.setPosition(-500,-500);
			choice2.setPosition(-500,-500);
			choice3.setPosition(-500,-500);
		}

		if(state == 1) //twoja misja rozpoczyna sie..
		{
			message.loadNewText(INTRO_TEXT_2);
			message.setCharacterSize(30);
		}

		if(state == 2) //co wybierzesz
		{
			message.loadNewText(INTRO_TEXT_3);
			message.setStyle(sf::Text::Style::Bold);
			message.setCharacterSize(40);
			choice1.setPosition(SCREEN_WIDTH * 0.2,SCREEN_HEIGHT * 0.75);
			choice2.setPosition(SCREEN_WIDTH * 0.65,SCREEN_HEIGHT * 0.75);
		}

		if (state == 3) //wybierz gracza
		{
			message.loadNewText(INTRO_TEXT_4);
			message.setStyle(sf::Text::Style::Regular);
			choice1.setTextString("Pani Halina");
			choice1.setPosition(SCREEN_WIDTH * 0.2 - choice1.getGlobalBounds().width / 2,SCREEN_HEIGHT * 0.75);
			choice1.setTextSize(30);
			choice2.setTextString("Haker");
			choice2.setPosition(SCREEN_WIDTH * 0.5 - choice1.getGlobalBounds().width / 2,SCREEN_HEIGHT * 0.75);
			choice2.setTextSize(30);
			choice3.setTextString("Mag");
			choice3.setPosition(SCREEN_WIDTH * 0.8 - choice1.getGlobalBounds().width / 2,SCREEN_HEIGHT * 0.75);
			choice3.setTextSize(30);
		}

		if (state == 4) // wybierz bron
		{
			message.loadNewText(INTRO_TEXT_5);
			choice1.setTextString(L"Telefon w \npanice do \ndzia³u IT");

			choice2.setTextString("Wiedza");

			choice3.setTextString(L"Zap³ata okupu\n w bitcoinach");
		}

		if (state == 5) //wybory zostaly dokonane
		{
			message.loadNewText(INTRO_TEXT_6);
			message2.loadNewText(INTRO_TEXT_7);
		}

		initialized = true;
	}


	/* set central position */
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
	if (state == 3)
	{
		message.setPosition(SCREEN_WIDTH / 2 - message.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.1);
	}
	if (state == 5)
	{
		message.setPosition(SCREEN_WIDTH / 2 - message.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.1);
		message2.setPosition(SCREEN_WIDTH / 2 + SCREEN_WIDTH * 0.3 - message.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.5);
	}
	
	/* update self writting text */
	message.updateText();
	if(state == 5 && message.isQueueEmpty())
		message2.updateText();
	space.updateText();


	/* buttons behaviour */
	if(state == 2)
	{
		if(choice1.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
		}

		if(choice2.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
		}
	}
	if(state == 3)
	{
		if(choice1.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
			this->data->characterChoice = 1;
		}

		if(choice2.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
			this->data->characterChoice = 2;
		}

		if(choice3.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
			this->data->characterChoice = 3;
		}
	}
	if(state == 4)
	{
		if(choice1.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
		}

		if(choice2.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
		}

		if(choice3.clicked(gm::Core::getWindow()))
		{
			click.play();
			Sleep(100);
			nextState = true;
		}
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
	if(state==0)
	{
		win.draw(choice1);
		win.draw(choice1);
		win.draw(choice1);
	}
	if(state == 0)
		win.draw(title);
	if(state == 1 || state == 5)
		win.draw(space);

	if(state == 2 && delay == false)
	{
		win.draw(choice1);
		win.draw(choice2);
	}
	delay = false;
	
	if(state == 3)
	{
		win.draw(choice1);
		win.draw(choice2);
		win.draw(choice3);
	}
	if(state == 4)
	{
		win.draw(choice1);
		win.draw(choice2);
		win.draw(choice3);
	}
	if(state == 5)
	{
		win.draw(message2);
	}

	win.draw(message);
	
	
	win.display();
}

