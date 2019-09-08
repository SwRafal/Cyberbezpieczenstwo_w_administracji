#include "OpenedDoc.h"

OpenedDoc::OpenedDoc(sf::Texture *texture, sf::Font *font)
{
	this->setTexture(*texture);
	this->setPosition((SCREEN_WIDTH - OPENED_DOC_WIDTH) / 2, (SCREEN_HEIGHT - OPENED_DOC_HEIGHT) / 2);
}

OpenedDoc::~OpenedDoc()
{
}

void OpenedDoc::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
}

bool OpenedDoc::update(sf::RenderWindow &win)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && win.hasFocus())
		return true;

	return false;
}
