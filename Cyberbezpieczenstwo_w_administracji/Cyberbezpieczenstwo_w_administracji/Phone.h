#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <queue>


#define PHONE_POS_X 140
#define PHONE_POS_Y 540
#define PHONE_WIDTH 105
#define PHONE_HEIGHT 170



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

