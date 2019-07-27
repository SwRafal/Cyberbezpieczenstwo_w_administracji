#include "PauseState.h"

void PauseState::fixOrigin()
{
	if(gm::Core::getWindow().getSize().x != SCREEN_WIDTH || gm::Core::getWindow().getSize().y != SCREEN_WIDTH)
	{
		int scaleX,scaleY;
		scaleX = gm::Core::getWindow().getSize().x / SCREEN_WIDTH;
		scaleY = gm::Core::getWindow().getSize().y / SCREEN_HEIGHT;

		buttonsbackground.setOrigin(buttonsbackground.getPosition().x + (buttonsbackground.getGlobalBounds().width * scaleX) / 2,
			buttonsbackground.getPosition().y + (buttonsbackground.getGlobalBounds().height * scaleY) / 2 );
	}
	else
		buttonsbackground.setOrigin(buttonsbackground.getPosition().x + buttonsbackground.getGlobalBounds().width / 2,
			buttonsbackground.getPosition().y + buttonsbackground.getGlobalBounds().height / 2);
}

PauseState::PauseState(gm::gameDataRef data) : data(data), resumeButton(*gm::Assets::getFont()),menuButton(*gm::Assets::getFont())
{

}


PauseState::~PauseState()
{

}

void PauseState::init()
{
	/* variables */
	resuming = false;

	scale = 0.05;
	opacity = 0;

	/* scene background */
	gm::Assets::LoadTexture("rounded rect shape", ROUNDED_RECT_SHAPE_FILEPATH);
	buttonsbackground.setTexture(*gm::Assets::getTexture("rounded rect shape"));
	fixOrigin();
	buttonsbackground.setPosition(gm::Core::getWindow().getSize().x / 2,
		gm::Core::getWindow().getSize().y / 2);
	
	
	

	background.setTexture(*gm::Assets::getTexture("pause bg"));

	rect.setSize(sf::Vector2f(gm::Core::getWindow().getSize().x,gm::Core::getWindow().getSize().y));
	rect.setFillColor(sf::Color(82, 82, 82,opacity));


	/* Resume button */
	resumeButton.setTextIdleColor(sf::Color::White);
	resumeButton.setTextAimedColor(sf::Color(230, 120, 255,255));
	resumeButton.setTextPressColor(sf::Color(216, 46, 255,255));
	resumeButton.setIdleColor(sf::Color::Transparent);
	resumeButton.setAimedColor(sf::Color::Transparent);
	resumeButton.setPressColor(sf::Color::Transparent);
	resumeButton.setSize(200,55);
	resumeButton.setTextSize(250);
	resumeButton.setTextString("Wznow gre");
	resumeButton.setPosition(gm::Core::getWindow().getSize().x / 2 - resumeButton.getGlobalBounds().width / 2,gm::Core::getWindow().getSize().y / 2 - resumeButton.getGlobalBounds().height / 2 - 50);

	/* Menu button */
	menuButton.setTextIdleColor(sf::Color::White);
	menuButton.setTextAimedColor(sf::Color(230, 120, 255,255));
	menuButton.setTextPressColor(sf::Color(216, 46, 255,255));
	menuButton.setIdleColor(sf::Color::Transparent);
	menuButton.setAimedColor(sf::Color::Transparent);
	menuButton.setPressColor(sf::Color::Transparent);
	menuButton.setSize(300,60);
	menuButton.setTextSize(70);
	menuButton.setTextString("Wyjscie do menu");
	menuButton.setPosition(gm::Core::getWindow().getSize().x / 2 - menuButton.getGlobalBounds().width / 2,gm::Core::getWindow().getSize().y / 2 - menuButton.getGlobalBounds().height / 2 + 60);

	/* click sound */
	gm::Assets::LoadSound("click", CLICK_SOUND_FILEPATH);
	clickSound.setBuffer(*gm::Assets::getSound("click"));
}

void PauseState::handleInput()
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
		case sf::Event::Resized:
			fixOrigin();
			buttonsbackground.setPosition(gm::Core::getWindow().getSize().x / 2,
		gm::Core::getWindow().getSize().y / 2);
			break;
		}
	}

	if(gm::Core::getEnteredChar() == 0x0000001B)
	{
		resuming = true;
	}

	if(resumeButton.clicked(gm::Core::getWindow()))
	{
		clickSound.play();
		Sleep(100);
		resuming = true;
	}

	if(menuButton.clicked(gm::Core::getWindow()))
	{
		clickSound.play();
		Sleep(100);
		resuming = true;
		data->returnToMenu = true;
	}
}

void PauseState::update(sf::RenderWindow &win)
{
	/* animation */
	if(resuming == true && opacity <= 0 && scale <= 0.05)
		data->machine.removeState();

	if(resuming == false && (opacity < 170 || scale < 1.0))
	{
		buttonsbackground.setScale(scale,scale);
		buttonsbackground.setPosition(gm::Core::getWindow().getSize().x / 2, gm::Core::getWindow().getSize().y / 2);
		if(scale < 1.0)
			scale = scale + 0.05;

		rect.setFillColor(sf::Color(82, 82, 82,opacity));
		if(opacity < 170)
			opacity = opacity + 10;
	}

	if(resuming == true && (opacity > 0 || scale > 0.05))
	{
		buttonsbackground.setScale(scale,scale);
		buttonsbackground.setPosition(gm::Core::getWindow().getSize().x / 2, gm::Core::getWindow().getSize().y / 2);
		if(scale > 0.05)
			scale = scale - 0.05;

		rect.setFillColor(sf::Color(82, 82, 82,opacity));
		if(opacity > 0)
			opacity = opacity - 10;
	}

	

}

void PauseState::draw(sf::RenderWindow& win)
{
	win.clear();

	win.draw(background);
	win.draw(rect);
	win.draw(buttonsbackground);

	if(opacity >= 170 && scale >= 1.0)
	{
		win.draw(resumeButton);
		win.draw(menuButton);
	}

	win.display();
}
