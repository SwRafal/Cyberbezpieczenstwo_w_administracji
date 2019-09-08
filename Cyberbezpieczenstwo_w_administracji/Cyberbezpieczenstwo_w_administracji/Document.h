#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <queue>


#define DOC_POS_X 250
#define DOC_POS_Y 600
#define DOC_WIDTH 219
#define DOC_HEIGHT 103

class Document : public gm::Button
{
public:

	sf::Sprite doc;
	//gm::Information text;

	Document(sf::Texture *tex);
	~Document();

	//void update(sf::RenderWindow &win);
	void draw(sf::RenderWindow& win);
};

