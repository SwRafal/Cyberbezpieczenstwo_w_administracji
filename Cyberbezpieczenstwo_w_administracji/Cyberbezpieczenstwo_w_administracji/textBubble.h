#pragma once
#include <SFML/Graphics.hpp>
#include "SelfWrittingText.h"
#include "Engine/Engine.h"
#include "Functions.h"

class textBubble : public sf::Sprite
{
public:
	/*sf::Text text;
	gm::SelfWrittingText text2;
	gm::Information text3;*/
	
	void setBubblePosition(int x,int y);
	void animate();
	void keepInPlace();

	gm::Information text;

	bool hidden = true;
	bool appearing;
	bool disappearing;
	bool showText;

	void closeBubble();
	void showBubble();
	void changeText(sf::String);

	float scale;
	float _maxScale;

	textBubble(sf::Texture *tex, float maxScale = 1);
	~textBubble();

	int posx;
	int posy;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	
	void draw(sf::RenderWindow& win);
};

