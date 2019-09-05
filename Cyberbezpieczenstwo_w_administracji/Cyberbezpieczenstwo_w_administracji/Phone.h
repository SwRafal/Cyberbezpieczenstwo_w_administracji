#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <queue>


#define PHONE_POS_X 10
#define PHONE_POS_Y 520
#define PHONE_WIDTH 122
#define PHONE_HEIGHT 196



class Phone : public gm::Button
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

	Phone();
	~Phone();


	//bool clicked(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);


	
	void draw(sf::RenderWindow& win);

};

