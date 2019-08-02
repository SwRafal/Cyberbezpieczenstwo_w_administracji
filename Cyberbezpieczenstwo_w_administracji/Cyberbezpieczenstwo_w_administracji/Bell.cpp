#include "Bell.h"

Bell::Bell(sf::Texture *texture)
{
	if (texture == nullptr)
		error_win_close();

	this->setTexture(texture);
	setSize(sf::Vector2f(BELL_WIDTH, BELL_HEIGHT));
	this->setTextureRect(sf::IntRect(sf::Vector2i(_frame*BELL_WIDTH, 0), sf::Vector2i(BELL_WIDTH, BELL_HEIGHT)));
	setIdleColor(sf::Color::White);
	setAimedColor(sf::Color(190, 200, 190));
	setPressColor(sf::Color(120, 150, 120));
	this->setPosition(sf::Vector2f(BELL_POS_X, BELL_POS_Y));

	this->setSize(0.8 * BELL_WIDTH,0.8 * BELL_HEIGHT);

	_animate = false;
	_repeat = 0;
	_frame = 0;
}

void Bell::draw(sf::RenderWindow &win)
{
	win.draw((sf::RectangleShape)*this);
}
bool Bell::update_rung(sf::RenderWindow &win)
{
	if (clicked(win))
	{
		_animate = true;
		return true;
	}

	if (_animate)
	{
		if (_repeat < BELL_ANIM_REPEATS)
		{
			if (_frame < BELL_ANIM_FRAMES)
			{
				_frame++;
			}
			else
			{
				_frame = 0;
				_repeat++;
			}
		}
		else
		{
			_animate = false;
			_repeat = 0;
		}
		

		this->setTextureRect(sf::IntRect(sf::Vector2i(_frame*BELL_WIDTH, 0),sf::Vector2i(BELL_WIDTH, BELL_HEIGHT)));
	}

	return false;
}