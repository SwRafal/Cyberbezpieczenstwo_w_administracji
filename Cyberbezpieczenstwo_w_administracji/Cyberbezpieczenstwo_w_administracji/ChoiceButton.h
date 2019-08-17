#pragma once
#include "Engine/TextButton.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class ChoiceButton
{
public:

	gm::TextButton text;
	sf::Sprite background;

	bool clicked(sf::RenderWindow &win);

	void setPosition(int x, int y);
	void setScale(float x, float y);
	void setText(sf::String str);

	void draw(sf::RenderWindow &win);


	ChoiceButton();
	~ChoiceButton();
};

