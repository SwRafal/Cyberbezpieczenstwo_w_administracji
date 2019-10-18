#include "DayOverState.h"

DayOverState::DayOverState(gm::gameDataRef data) : data(data), knowledge(*gm::Assets::getFont())
{
}


DayOverState::~DayOverState()
{
}

void DayOverState::init()
{
	gm::Assets::LoadTexture("gameoverbutton", GAME_OVER_BUTTON);
	next.setTexture(gm::Assets::getTexture("gameoverbutton"));

	knowledge.setTextSize(24);
	knowledge.setTextColor(sf::Color::White);
	knowledge.setFillColor(sf::Color::Transparent);
	knowledge.setPosition(140, 144);
	knowledge.setSize(1225 - 43, 557 - 144);

	next.setIdleColor(sf::Color::White);
	next.setAimedColor(sf::Color(190, 200, 190));
	next.setPressColor(sf::Color(120, 150, 120));
	next.setSize(57, 57);
	next.setPosition(1100, 592);

	arial.loadFromFile("resources/fonts/arialbd.ttf");
	text.setFont(arial);
	text.setCharacterSize(24);
	text.setStyle(sf::Text::Style::Regular);
	text.setFillColor(sf::Color::White);
	text.setPosition(140, 100);
	text.setString(L"EKRAN PODSUMOWANIA DNIA");


	knowledge.setTextString(L"Gratulacje! Ukoñczy³eœ kolejny dzieñ pracy!\nLiczba upomnieñ: ");
	knowledge.setTextString(knowledge.getTextString() + std::to_string(data->nagany));
	knowledge.setTextString(knowledge.getTextString() + "\n\nZdobyta wiedza:\n" + data->knowledge);

	text_alpha = 0;
	state = 0;

	gm::Assets::LoadTexture("sunset", "resources/textures/sunset.png");
	background.setTexture(*gm::Assets::getTexture("sunset"));
}

void DayOverState::handleInput()
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

void DayOverState::update(sf::RenderWindow& win)
{
	if(text_alpha < 255)
		text_alpha+=2;
	if (text_alpha > 255)
		text_alpha = 255;
	knowledge.setTextColor(sf::Color(255, 255, 255, text_alpha));
	text.setFillColor(sf::Color(255,255,255,text_alpha));

	if (next.clicked(win))
	{
		data->machine.removeState();
	}
}

void DayOverState::draw(sf::RenderWindow& win)
{
	win.clear(sf::Color::Black);
	win.draw(background);
	win.draw(text);
	knowledge.draw(win);
	win.draw(next);

	win.display();
}



