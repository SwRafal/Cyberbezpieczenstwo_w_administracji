#include "OpenedBook.h"

OpenedBook::OpenedBook(sf::Texture *texture, sf::Font *font)
{
	this->setTexture(*texture);
	this->setPosition(BOOK_OPENED_POS_X, BOOK_OPENED_POS_Y);
	infoL = new gm::Information(*font, sf::Vector2f(BOOK_PAGE1_POS_X, BOOK_PAGE1_POS_Y), sf::Vector2f(BOOK_PAGE_WIDTH, BOOK_PAGE_HEIGHT), 18);
	infoR = new gm::Information(*font, sf::Vector2f(BOOK_PAGE2_POS_X, BOOK_PAGE2_POS_Y), sf::Vector2f(BOOK_PAGE_WIDTH, BOOK_PAGE_HEIGHT), 18);

	infoL->setFillColor(sf::Color::Transparent);
	infoL->setTextColor(sf::Color::Black);
	infoR->setFillColor(sf::Color::Transparent);
	infoR->setTextColor(sf::Color::Black);

	infoL->setTextString(L"Przk�adowy tekst");
	infoR->setTextString(L"Litwo, Ojczyzno moja! ty jeste� jak zdrowie Ile ci� trzeba ceni�, ten tylko si� dowie, Kto ci� straci�. Dzi� pi�kno�� tw� w ca�ej ozdobie Widz� i opisuj�, bo t�skni� po tobie.");
}

OpenedBook::~OpenedBook()
{
	delete infoL;
	infoL = nullptr;
	delete infoR;
	infoR = nullptr;
}

void OpenedBook::draw(sf::RenderWindow &win)
{
	win.draw((sf::Sprite)*this);
	infoL->draw(win);
	infoR->draw(win);
}
bool OpenedBook::update(sf::RenderWindow &win)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && win.hasFocus())
		return true;

	return false;
}

void OpenedBook::setInfoL(const sf::String &info)
{
	infoL->setTextString(info);
}
void OpenedBook::setInfoR(const sf::String &info)
{
	infoR->setTextString(info);
}