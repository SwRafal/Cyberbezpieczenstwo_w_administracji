#include "MenuState.h"
#include "GameState.h"
#include "Windows.h"
#include "IntroState.h"


MenuState::MenuState(gm::gameDataRef data) : data(data), playButton(*gm::Assets::getFont()),exitButton(*gm::Assets::getFont()),intro(*gm::Assets::getFont())
{

}


MenuState::~MenuState()
{
}

void MenuState::init()
{
	/* Play button */
	playButton.setPosition(60,500);
	playButton.setTextIdleColor(sf::Color::White);
	playButton.setTextAimedColor(sf::Color(230, 120, 255,255));
	playButton.setTextPressColor(sf::Color(216, 46, 255,255));
	playButton.setIdleColor(sf::Color::Transparent);
	playButton.setAimedColor(sf::Color::Transparent);
	playButton.setPressColor(sf::Color::Transparent);
	playButton.setSize(200,55);
	playButton.setTextSize(250);
	playButton.setTextString("Nowa gra");

	/* Exit button */
	exitButton.setPosition(36,575);
	exitButton.setTextIdleColor(sf::Color::White);
	exitButton.setTextAimedColor(sf::Color(230, 120, 255,255));
	exitButton.setTextPressColor(sf::Color(216, 46, 255,255));
	exitButton.setIdleColor(sf::Color::Transparent);
	exitButton.setAimedColor(sf::Color::Transparent);
	exitButton.setPressColor(sf::Color::Transparent);
	exitButton.setSize(200,40);
	exitButton.setTextSize(70);
	exitButton.setTextString("Wyjscie");

	/* intro button */
	intro.setPosition(0,0);
	intro.setTextIdleColor(sf::Color::White);
	intro.setTextAimedColor(sf::Color(230, 120, 255,255));
	intro.setTextPressColor(sf::Color(216, 46, 255,255));
	intro.setIdleColor(sf::Color::Transparent);
	intro.setAimedColor(sf::Color::Transparent);
	intro.setPressColor(sf::Color::Transparent);
	intro.setSize(200,40);
	intro.setTextSize(70);
	intro.setTextString("intro");

	/* animated background */
	animationCounteri = 0;
	animationCounterj = 0;
	gm::Assets::LoadTexture("menu bg", MENU_BACKGROUND_ANIMATION_FILEPATH);
	if (gm::Assets::getTexture("menu bg") == nullptr)
	{
		MessageBoxA(NULL, "b³¹d - brak tekstury", "b³¹d", MB_OK | MB_ICONEXCLAMATION);
		exit(EXIT_FAILURE);
	}
	background_animation_spritesheet.setTexture(*gm::Assets::getTexture("menu bg"));

	/* click sound */
	gm::Assets::LoadSound("click", CLICK_SOUND_FILEPATH);
	clickSound.setBuffer(*gm::Assets::getSound("click"));
}

void MenuState::handleInput()
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

	if(playButton.clicked(gm::Core::getWindow()))
	{
		clickSound.play();
		Sleep(100);
		data->machine.addState(gm::StateRef(new GameState (this->data)));
	}

	if(exitButton.clicked(gm::Core::getWindow()))
	{
		clickSound.play();
		Sleep(100);
		exit(EXIT_SUCCESS);
	}

	if(intro.clicked(gm::Core::getWindow()))
	{
		clickSound.play();
		Sleep(100);
		data->machine.addState(gm::StateRef(new IntroState (this->data))); 
		
	}
		
}

void MenuState::update(sf::RenderWindow &win)
{
	background_animation_spritesheet.setTextureRect(sf::IntRect(animationCounteri * 500,animationCounterj * 281,500,281));
	background_animation_spritesheet.setScale(2.56,2.56227758007);

	if(animationCounterj!=16)
		animationCounteri++;
	
	if(animationCounteri == 13)
	{
		animationCounteri = 0;
		animationCounterj++;
	}
		
	if(animationCounterj == 15)
		animationCounterj = 0;
}

void MenuState::draw(sf::RenderWindow& win)
{
	win.clear();

	win.draw(background_animation_spritesheet);
	win.draw(playButton);
	win.draw(exitButton);
	win.draw(intro);
	
	win.display();
}
