#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <queue>


#define MOBILE_POS_X 740
#define MOBILE_POS_Y 550
#define MOBILE_WIDTH 77
#define MOBILE_HEIGHT 162

#define MOBILE_VIEW_POS_X 440
#define MOBILE_VIEW_POS_Y 30
#define MOBILE_VIEW_WIDTH 303
#define MOBILE_VIEW_HEIGHT 636



class Mobile : public gm::Button
{
public:
	sf::Sound vibration;

	sf::Sprite mobile_view;
	gm::Information text;

	bool calling;
	bool pickedUp;

	void call();


	Mobile(sf::Texture *tex);
	~Mobile();


	//bool clicked(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);
	void draw(sf::RenderWindow& win);

	void draw_view(sf::RenderWindow &win);
};

