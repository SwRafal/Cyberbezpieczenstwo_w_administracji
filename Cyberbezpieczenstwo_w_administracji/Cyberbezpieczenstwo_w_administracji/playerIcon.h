#pragma once
#include "Engine/Engine.h"
#include <queue>

#define SIZE_X 396
#define SIZE_Y 335

#define POS_X -400
#define POS_Y 17

#define FINAL_POS_X 10

class PlayerIcon
{
public:
	PlayerIcon(int character);
	~PlayerIcon();

	void show();
	void hide();

	bool nextLine();
	void addToQueue(sf::String str);

	void animate();
	void draw(sf::RenderWindow &win);

	sf::Sprite chat;
	gm::Information text;

	std::queue<sf::String> text_queue;

	int state;

	bool hidden;

	bool appearing;
	bool disappearing;
	bool ready;
private:
	sf::Sprite icon;
};