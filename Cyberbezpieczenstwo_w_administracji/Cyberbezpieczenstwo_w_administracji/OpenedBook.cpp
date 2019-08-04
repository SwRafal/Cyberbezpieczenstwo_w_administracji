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

	infoL->setTextString(L"To jest jaki� przyk�adowy a a tek�cior.  I tu dalej idzie jaki� takie tek�cik. No to jeszcze dowalmy jedno zdanie, tak �eby sprawdzi�"
						 L"jak to dzia�a co nie. ");
	infoR->setTextString(L"To jest jaki� dodatkowy tek�cior. Sz�a dzieweczka do laseczka do zielonego hahahaha. Bum cum drup cum lama kama elo melo 3 2 0"
						 L"Tu b�d� kiedy� informacje co nie.");
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