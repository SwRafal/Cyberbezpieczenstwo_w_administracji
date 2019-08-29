#include "OpenPC.h"

OpenPC::OpenPC(sf::Texture *texture, sf::Font *font)
{
	this->setTexture(*texture);
	this->setPosition(PC_OPENED_POS_X, PC_OPENED_POS_Y);
}
OpenPC::~OpenPC()
{

}

void OpenPC::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
}

bool OpenPC::update(sf::RenderWindow &win)
{
	//...
	return false;
}