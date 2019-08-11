#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class dayx : public sf::RectangleShape
{
public:
	dayx(int _dayNumber);
	~dayx();
	sf::Text title;
	int dayNumber;
	void update();
	int opacity;
	int timer;
	bool show;
	int opacitySpeed;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void reset();
	
};

