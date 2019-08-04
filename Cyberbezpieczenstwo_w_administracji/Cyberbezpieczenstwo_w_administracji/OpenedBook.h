#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define BOOK_OPENED_POS_X 385
#define BOOK_OPENED_POS_Y 180
#define BOOK_OPENED_WIDTH 510
#define BOOK_OPENDE_HEIGHT 362

#define BOOK_PAGE_WIDTH 210
#define BOOK_PAGE_HEIGHT 325

#define BOOK_PAGE1_POS_X 410
#define BOOK_PAGE1_POS_Y 190
#define BOOK_PAGE2_POS_X 650
#define BOOK_PAGE2_POS_Y 190

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