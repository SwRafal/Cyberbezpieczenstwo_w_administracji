#include "Book.h"

/*Maintenance(? ) */

Book::Book(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(BOOK_WIDTH, BOOK_HEIGHT));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(BOOK_POS_X, BOOK_POS_Y));

	_opened = false;
}

void Book::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}
void Book::update(sf::RenderWindow &win)
{
	if (clicked(win))
		_opened = true;
}

void Book::open()
{
	_opened = true;
}
void Book::close()
{
	_opened = false;
}