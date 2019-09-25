#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include <vector>

#define PHISHING_POS_X 
#define PHISHING_POS_Y 
#define PHISHING_WIDTH 
#define PHISHING_HEIGHT 

class Phishing
{
public:
	bool turned_on;
	bool show_content;
	bool good_mail;
	sf::Sprite background;
	sf::Sprite screen;

	sf::Int32 randomize_time;

	std::vector<gm::TextButton*>mails;

	gm::Information* content = nullptr;
	gm::TextButton *accept = nullptr;
	gm::TextButton *decline = nullptr;

	Phishing();
	~Phishing();

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);
};