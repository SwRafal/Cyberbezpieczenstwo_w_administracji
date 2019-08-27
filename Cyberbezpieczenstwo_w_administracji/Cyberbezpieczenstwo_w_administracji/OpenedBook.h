#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define BOOK_OPENED_POS_X 182
#define BOOK_OPENED_POS_Y 24
#define BOOK_OPENED_WIDTH 915
#define BOOK_OPENDE_HEIGHT 672

#define BOOK_PAGE_WIDTH 405
#define BOOK_PAGE_HEIGHT 620

#define BOOK_PAGE1_POS_X 222
#define BOOK_PAGE1_POS_Y 45
#define BOOK_PAGE2_POS_X 650
#define BOOK_PAGE2_POS_Y 45

class OpenedBook : public sf::Sprite
{
private:
	gm::Information *infoL = nullptr, *infoR = nullptr;
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	OpenedBook(sf::Texture *texture, sf::Font *font);
	~OpenedBook();

	void draw(sf::RenderWindow &win);
	bool update(sf::RenderWindow &win); //GameState can know if book should be closed

	void setInfoL(const sf::String &info);
	void setInfoR(const sf::String &info);

	sf::String getInfoL() { return infoL->getTextString(); }
	sf::String getInfoR() { return infoR->getTextString(); }
	sf::String getInfo() { return infoL->getTextString() + infoR->getTextString(); }
};