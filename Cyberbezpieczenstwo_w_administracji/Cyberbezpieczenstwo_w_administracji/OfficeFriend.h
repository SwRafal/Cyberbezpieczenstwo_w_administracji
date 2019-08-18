#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include "textBubble.h"

/*DETAILS (position...)*/

#define SIZE_X 110
#define SIZE_Y 133

#define POS_X 1390
#define POS_Y 260

#define FINAL_POS_X 1160

class OfficeFriend : public sf::Sprite
{
public:

	bool appearing;
	bool disappearing;
	bool ready;
	bool active;

	void animate();
	void show();
	void hide();

	void draw(sf::RenderWindow &win);

	std::queue<sf::String> text_queue;

	bool nextLine();
	void addToQueue(sf::String str);

	void setButtonActive();
	void setButtonInactive();

	
	sf::Sprite chat;
	gm::Information text;

	gm::Button button;
	sf::Sprite img;
	bool clicked;

	int state;
	

	

	OfficeFriend(sf::Texture *texture);
	~OfficeFriend();
};

