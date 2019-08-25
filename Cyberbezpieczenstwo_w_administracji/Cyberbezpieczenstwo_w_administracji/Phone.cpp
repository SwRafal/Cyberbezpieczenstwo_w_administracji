#include "Phone.h"




Phone::Phone() : text(*gm::Assets::getFont())
{
	/* set textures */
	gm::Assets::LoadSound("ringtone", PHONE_RINGING_FILEPATH);
	ringtone.setBuffer(*gm::Assets::getSound("ringtone"));

	gm::Assets::LoadTexture("phone", TEXTURE_TELEPHONE);
	if (gm::Assets::getTexture("phone") == nullptr)
		error_win_close();
	
	this->setTexture(gm::Assets::getTexture("phone"));

	gm::Assets::LoadTexture("text bubble", TEXTURE_TEXT_BUBBLE);
	if (gm::Assets::getTexture("text bubble") == nullptr)
		error_win_close();

	bubble.setTexture(*gm::Assets::getTexture("text bubble"));

	/* set position */

	setSize(sf::Vector2f(PHONE_WIDTH, PHONE_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(PHONE_POS_X, PHONE_POS_Y));

	if(gm::Assets::getTexture("text bubble") == nullptr)
		gm::Assets::LoadTexture("text bubble", TEXTURE_TEXT_BUBBLE);
	bubble.setTexture(*gm::Assets::getTexture("text bubble"));
	bubble.setPosition(0,-300);

	/* variables */

	calling = true;
	pickedUp = false;

	showText = false;
	showButtons = false;

	choice = 0;

	text_queue.push(L"siema nie moge teraz rozmawiac");
	text_queue.push(L"przeciez to ty zadzwoniles");

	bubble.setScale(0.5,0.5);
	bubble.setPosition(50,50);




}


Phone::~Phone()
{

}


void Phone::update(sf::RenderWindow& win)
{
	if(clicked(win))
	{
		if(calling)
			pickedUp = true;

		calling = false;
		
	}

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


	

	
}

void Phone::draw(sf::RenderWindow& win)
{
	win.draw((sf::RectangleShape)*this);
	win.draw((sf::Sprite)bubble);
	//win.draw(text);
}

void Phone::call()
{
	calling = true;
}

void Phone::addToQueue(sf::String str)
{
	text_queue.push(str);
}