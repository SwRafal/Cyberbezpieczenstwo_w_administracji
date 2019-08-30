#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <queue>


#define MOBILE_POS_X 800
#define MOBILE_POS_Y 480
#define MOBILE_WIDTH 101
#define MOBILE_HEIGHT 212



class Mobile : public gm::Button
{
public:
	sf::Sound ringtone;

	gm::Information text;
	sf::Sprite textBackground;
	gm::TextButton arrowButton;
	sf::CircleShape arrow;

	;
	bool calling;
	bool pickedUp;

	bool showText;
	bool showButtons;
	bool showArrowButton;



	int choice;

	std::queue<sf::String> text_queue;

	void call();
	bool nextLine();
	void addToQueue(sf::String str);

	Mobile(sf::Texture *tex);
	~Mobile();


	//bool clicked(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);



	void draw(sf::RenderWindow& win);

};

