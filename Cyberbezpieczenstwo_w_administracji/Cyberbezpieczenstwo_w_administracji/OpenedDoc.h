#pragma once
#include "Engine/Engine.h"
#include "Functions.h"

#define OPENED_DOC_X 0
#define OPENED_DOC_Y 0
#define OPENED_DOC_WIDTH 310
#define OPENED_DOC_HEIGHT 422

class OpenedDoc : public sf::Sprite
{
public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) = delete;
	OpenedDoc(sf::Texture *texture, sf::Font *font);
	~OpenedDoc();

	void draw(sf::RenderWindow &win);
	bool update(sf::RenderWindow &win); //GameState can know if book should be closed
};