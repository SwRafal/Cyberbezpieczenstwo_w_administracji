#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>


class dayx : public sf::RectangleShape
{
public:
	dayx(int &_dayNumber);
	~dayx();
	sf::Text title;
	int *dayNumber;
	void update();
	int opacity;
	int timer;
	bool show;
	int opacitySpeed;

	sf::Sprite background;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void reset();
	void nextDay();

	bool finished;
	
};

