#include "ChoiceButton.h"
#include "Engine/Core.h"
#include "Engine/Assets.h"
#include "Functions.h"


ChoiceButton::ChoiceButton() : text(*gm::Assets::getFont())
{
	if(gm::Assets::getTexture("text bubble") == nullptr)
		gm::Assets::LoadTexture("text bubble",TEXTURE_TEXT_BUBBLE);

	if(gm::Assets::getTexture("text bubble") == nullptr)
		error_win_close();

	background.setTexture(*gm::Assets::getTexture("text bubble"));
	background.setScale(0.4,0.4);

	text.setIdleColor(sf::Color::Transparent);
	text.setAimedColor(sf::Color::Transparent);
	text.setPressColor(sf::Color::Transparent);

	text.setTextIdleColor(sf::Color::Black);
	text.setTextAimedColor(sf::Color(166, 166, 166,255));
	text.setTextPressColor(sf::Color(157, 199, 197,255));
	
	text.setSize(background.getGlobalBounds().width,background.getGlobalBounds().height);
	text.setTextSize(background.getScale().x * 40);
	text.setTextString("");

	background.setPosition(100,100);
	text.setPosition(background.getPosition());

	

}

bool ChoiceButton::clicked(sf::RenderWindow &win)
{
	return text.clicked(win);
}



ChoiceButton::~ChoiceButton()
{
}

void ChoiceButton::setPosition(int x, int y)
{
	text.setPosition(x,y);
	background.setPosition(x,y);
}

void ChoiceButton::setScale(float x, float y)
{
	background.setScale(x,y);
	text.setSize(background.getGlobalBounds().width,background.getGlobalBounds().height);
	text.setTextSize(background.getScale().x * 40);
}

void ChoiceButton::setText(sf::String str)
{
	text.setTextString(str);
}

void ChoiceButton::draw(sf::RenderWindow& win)
{
	win.draw(background);
	win.draw((sf::RectangleShape)text);
}

