#include "GameOverState.h"
#include "MenuState.h"


GameOverState::GameOverState(gm::gameDataRef data) : data(data), reason(*gm::Assets::getFont())
{
}


GameOverState::~GameOverState()
{
}

void GameOverState::init()
{
	gm::Assets::LoadTexture("gameoverbg",GAME_OVER_BACKGROUND);
	gm::Assets::LoadTexture("gameoverbutton", GAME_OVER_BUTTON);

	background.setTexture(*gm::Assets::getTexture("gameoverbg"));
	next.setTexture(gm::Assets::getTexture("gameoverbutton"));

	reason.setTextSize(20);
	reason.setTextColor(sf::Color::White);
	reason.setFillColor(sf::Color::Transparent);
	reason.setPosition(43,144);
	reason.setSize( 1225 - 43, 557 - 144);

	next.setIdleColor(sf::Color::White);
	next.setAimedColor(sf::Color(190, 200, 190));
	next.setPressColor(sf::Color(120, 150, 120));
	next.setSize(57,57);
	next.setPosition( 1100 , 592);

	arial.loadFromFile("resources/fonts/arialbd.ttf");
	loadingText.setFont(arial);
	loadingText.setCharacterSize(24);
	loadingText.setStyle(sf::Text::Style::Regular);
	loadingText.setFillColor(sf::Color::White);
	loadingText.setPosition(140,650);
	loadingText.move(0,-4);

	loadingBar.setSize(sf::Vector2f(1,34));
	loadingBar.setPosition(43,603);
	loadingBar.setFillColor(sf::Color::White);

	reason.setTextString(data->whyFired);


	animated = false;
	state = 0;
	loadingNumber = 1;
	loadingBarSize = 1;
}

void GameOverState::handleInput()
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

void GameOverState::update(sf::RenderWindow& win)
{
	if(animated && state == 1)
	{
		sf::String s = L"-iloœæ przepracowanych dni: ";
		s = s + std::to_string(data->day) + L"\n\n-iloœæ upomnieñ: " + std::to_string(data->nagany);
	}

	if(!animated)
	{
		if(loadingBarSize < 100)
		{
			loadingBarSize++;
			loadingNumber = loadingBarSize;
			loadingBar.setSize(sf::Vector2f((float)(loadingBarSize * 7.82),34));

			sf::String s = std::to_string(loadingNumber);
			s = s + "%";
			loadingText.setString(s);
		}
		else
			animated = true;
	}

	if(animated)
	{
		if(next.clicked(win))
		{
			if(state == 0)
			{
				state = 1;
				sf::String s = L"-iloœæ przepracowanych dni: ";
				s = s + std::to_string(data->day) + L"\n\n-iloœæ nagan: " + std::to_string(data->nagany);
				reason.setTextString(s);
			}
			else if(state == 1)
			{
				data->machine.addState(gm::StateRef(new MenuState (this->data)));
			}
		}
	}

}

void GameOverState::draw(sf::RenderWindow& win)
{
	win.clear();

	win.draw(background);
	if(animated)
		reason.draw(win);
	win.draw(loadingBar);
	win.draw(loadingText);

	if(animated)
		win.draw(next);

	win.display();
}



