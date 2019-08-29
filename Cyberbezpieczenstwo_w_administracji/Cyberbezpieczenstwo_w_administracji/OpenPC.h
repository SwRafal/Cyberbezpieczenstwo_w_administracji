#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define PC_OPENED_POS_X 50
#define PC_OPENED_POS_Y 50

class OpenPC : public sf::Sprite
{
private:
	//Rzeczy w komputerze
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	OpenPC(sf::Texture *texture, sf::Font *font);
	~OpenPC();

	void draw(sf::RenderWindow &win);
	bool update(sf::RenderWindow &win); //GameState can know if book should be closed
};