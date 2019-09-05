#pragma once
#include "Engine/Engine.h"
#include "Functions.h"
#include "OpenedBook.h"

#define BOOK_POS_X 550
#define BOOK_POS_Y 445
#define BOOK_WIDTH 162 //203
#define BOOK_HEIGHT 146 //183

class Book : public gm::Button
{
private:
	bool _opened;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	Book(sf::Texture *texture);

	void draw(sf::RenderWindow &win);
	void update(sf::RenderWindow &win);

	void open();
	void close();

	bool isOpened() { return _opened; }
};

