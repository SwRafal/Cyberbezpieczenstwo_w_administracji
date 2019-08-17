#pragma once
#include "Engine/TextButton.h"
#include <SFML/Graphics/Sprite.hpp>

class ChoiceButton
{
public:

	gm::TextButton text;
	sf::Sprite background;



	ChoiceButton();
	~ChoiceButton();
};

