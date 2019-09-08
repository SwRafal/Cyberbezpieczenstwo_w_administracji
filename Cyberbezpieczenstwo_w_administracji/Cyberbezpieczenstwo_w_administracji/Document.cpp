#include "Document.h"

/*Maintenance(?)*/

Document::Document(sf::Texture *tex)// : text(*gm::Assets::getFont())
{
	this->setTexture(tex);

	/* set position */

	this->setSize(sf::Vector2f(DOC_WIDTH, DOC_HEIGHT));
	this->setIdleColor(sf::Color::White);
	this->setAimedColor(sf::Color(190, 200, 190));
	this->setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(DOC_POS_X, DOC_POS_Y));

	doc.setTexture(*gm::Assets::getTexture("DOC"));
	
}

Document::~Document()
{
}

void Document::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}