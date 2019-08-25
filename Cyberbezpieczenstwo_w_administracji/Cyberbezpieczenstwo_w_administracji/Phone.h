#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <queue>

#define PHONE_POS_X 10
#define PHONE_POS_Y 460
#define PHONE_WIDTH 122
#define PHONE_HEIGHT 196



class Phone : public gm::Button
{
public:
	sf::Sound ringtone;

	sf::Sprite bubble;
	gm::Information text;

	gm::Button button;
	sf::Sprite img;

	
	bool opened;
	bool calling;
	bool pickedUp;

	bool showText;
	bool showButtons;

	int choice;

	std::queue<sf::String> text_queue;

	void call();

	void addToQueue(sf::String str);

	Phone();
	~Phone();


	//bool clicked(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	void draw(sf::RenderWindow &win);

};

