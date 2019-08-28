#include "Eyelids.h"

Eyelids::Eyelids()
{
	eyelids = new sf::RectangleShape[2];
	eyelids[0].setFillColor(sf::Color(0, 0, 0, 0));
	eyelids[0].setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2));
	eyelids[0].setOrigin(sf::Vector2f(0, eyelids[0].getSize().y));
	eyelids[0].setPosition(sf::Vector2f(0, 0));
	eyelids[1].setFillColor(sf::Color(0, 0, 0, 0));
	eyelids[1].setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2));
	eyelids[1].setPosition(sf::Vector2f(0, SCREEN_HEIGHT));

	up_eyelid_height = 0;
	down_eyelid_height = SCREEN_HEIGHT;
	up_eyelid_destination = 0;
	down_eyelid_destination = SCREEN_HEIGHT;
}

Eyelids::~Eyelids()
{
	delete[] eyelids;
	eyelids = nullptr;
}

void Eyelids::adjust()
{
	up_eyelid_destination = (float)closed_eyes_lvl / FULL_CLOSED_EYES * eyelids[0].getSize().y;
	eyelids[0].setFillColor(sf::Color(0, 0, 0, 210 + 15 * closed_eyes_lvl));

	down_eyelid_destination = SCREEN_HEIGHT - (float)closed_eyes_lvl / FULL_CLOSED_EYES * eyelids[0].getSize().y;
	eyelids[1].setFillColor(sf::Color(0, 0, 0, 210 + 15 * closed_eyes_lvl));
}

void Eyelids::open()
{
	closed_eyes_lvl = 0;
	adjust();
}
void Eyelids::close()
{
	closed_eyes_lvl = FULL_CLOSED_EYES;
	adjust();
}
void Eyelids::decreaseLvl()
{
	if (closed_eyes_lvl > 0)
		closed_eyes_lvl--;

	adjust();
}
void Eyelids::increaseLvl()
{
	if (closed_eyes_lvl < FULL_CLOSED_EYES)
		closed_eyes_lvl++;

	adjust();
}
void Eyelids::setLvl(unsigned short lvl)
{
	if (lvl < 0)
		closed_eyes_lvl = 0;
	else if (lvl > FULL_CLOSED_EYES)
		closed_eyes_lvl = FULL_CLOSED_EYES;
	else
		closed_eyes_lvl = lvl;

	adjust();
}


void Eyelids::update()
{
	if (up_eyelid_height < up_eyelid_destination)
		up_eyelid_height+=5;
	if (up_eyelid_height > up_eyelid_destination)
		up_eyelid_height = up_eyelid_destination;
	eyelids[0].setPosition(sf::Vector2f(0, up_eyelid_height));

	if (down_eyelid_height > down_eyelid_destination)
		down_eyelid_height-=5;
	if (down_eyelid_height < down_eyelid_destination)
		down_eyelid_height = down_eyelid_destination;
	eyelids[1].setPosition(sf::Vector2f(0, down_eyelid_height));
}

void Eyelids::draw(sf::RenderWindow &win)
{
	win.draw(eyelids[0]);
	win.draw(eyelids[1]);
}