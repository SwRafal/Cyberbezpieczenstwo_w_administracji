#include "Phone.h"




Phone::Phone() : text(*gm::Assets::getFont()), arrowButton(*gm::Assets::getFont())
{
	/* set textures */
	gm::Assets::LoadSound("ringtone", PHONE_RINGING_FILEPATH);
	ringtone.setBuffer(*gm::Assets::getSound("ringtone"));

	gm::Assets::LoadTexture("phone", TEXTURE_TELEPHONE);
	if (gm::Assets::getTexture("phone") == nullptr)
		error_win_close();
	
	this->setTexture(gm::Assets::getTexture("phone"));

	gm::Assets::LoadTexture("bubble2", TEXTURE_TEXT_BUBBLE);

	textBackground.setTexture(*gm::Assets::getTexture("bubble2"));
	


	


	/* set position */

	this->setSize(sf::Vector2f(PHONE_WIDTH, PHONE_HEIGHT));
	this->setIdleColor(sf::Color::White);
	this->setAimedColor(sf::Color(190, 200, 190));
	this->setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(PHONE_POS_X, PHONE_POS_Y));

	textBackground.setPosition(SCREEN_WIDTH / 2 - textBackground.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - textBackground.getGlobalBounds().height / 2 - 100);

	arrowButton.setTextIdleColor(sf::Color::Black);
	arrowButton.setTextAimedColor(sf::Color(50, 50, 50,255));
	arrowButton.setTextPressColor(sf::Color::White);
	arrowButton.setIdleColor(sf::Color::Transparent);
	arrowButton.setAimedColor(sf::Color::Transparent);
	arrowButton.setPressColor(sf::Color::Transparent);
	
	arrowButton.setTextString(L">");
	arrowButton.setSize(50,50);
	arrowButton.setTextSize(30);
	arrowButton.setPosition(785,285);

	text.setSize(textBackground.getGlobalBounds().width * 0.98,textBackground.getGlobalBounds().height * 0.98);
	text.setPosition(textBackground.getPosition().x + 4, textBackground.getPosition().y);
	text.setTextColor(sf::Color::Black);
	text.setFillColor(sf::Color::Transparent);
	text.setTextSize(20);

	

	/* variables */

	calling = false;
	pickedUp = false;

	showText = false;
	showButtons = false;
	showArrowButton = false;

	choice = 0;

	text_queue.push(L"siema nie moge teraz rozmawiac");
	text_queue.push(L"przeciez to ty zadzwoniles");
}


Phone::~Phone()
{

}


void Phone::update(sf::RenderWindow& win)
{
	if(calling)
	{
		if(ringtone.getStatus() == sf::Sound::Stopped)
			ringtone.play();

		if(this->getPosition().x == PHONE_POS_X)
			this->move(1,0);
		else
			this->setPosition(PHONE_POS_X,this->getPosition().y);

		if(this->getPosition().y == PHONE_POS_Y)
			this->move(0,1);
		else
			this->setPosition(this->getPosition().x,PHONE_POS_Y);
	}
	else
		ringtone.stop();

	if(clicked(win))
	{
		if(calling)
		{
			nextLine();
			showText = true;
			pickedUp = true;
		}
		calling = false;
	}

	if(arrowButton.clicked(win))
	{
		if(!nextLine())
		{
			pickedUp = false;
		}
	}

}



void Phone::draw(sf::RenderWindow& win)
{
	win.draw((sf::RectangleShape)*this);
	if(pickedUp)
	{
		win.draw(textBackground);
		text.draw(win);
		win.draw(arrowButton);
	}
}

void Phone::call()
{
	calling = true;
}

void Phone::addToQueue(sf::String str)
{
	text_queue.push(str);
}

bool Phone::nextLine()
{
	if(!text_queue.empty())
	{
		text.setTextString(text_queue.front());
		text_queue.pop();
		return true;
	}
	return false;
}