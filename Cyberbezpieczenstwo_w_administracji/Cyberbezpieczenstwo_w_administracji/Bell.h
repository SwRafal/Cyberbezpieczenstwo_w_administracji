#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define BELL_POS_X 1160
#define BELL_POS_Y 165
#define BELL_WIDTH 89
#define BELL_HEIGHT 104

#define BELL_ANIM_FRAMES 2
#define BELL_ANIM_REPEATS 5

class Bell : public gm::Button
{
private:
	bool _animate;
	unsigned short _frame;
	unsigned short _repeat;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Bell(sf::Texture *texture);

	void draw(sf::RenderWindow &win);
	bool update_rung(sf::RenderWindow &win);//Returns bool value, so GameState knows if we rang the bell
};