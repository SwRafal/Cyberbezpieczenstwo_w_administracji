#include "Button.h"
#include <iostream>

namespace gm
{
	void Button::setSize(float x, float y)
	{
		sf::RectangleShape::setSize(sf::Vector2f(x, y));
	}

	/*Button status' colors*/
	void Button::setIdleColor(const sf::Color &color)
	{
		idle_color = color;
	}

	void Button::setAimedColor(const sf::Color &color)
	{
		aimed_color = color;
	}

	void Button::setPressColor(const sf::Color &color)
	{
		press_color = color;
	}

	/*Main methods*/
	bool Button::aimed(sf::RenderWindow &win)
	{
		sf::Vector2f world_mouse = win.mapPixelToCoords((sf::Vector2i)sf::Mouse::getPosition(win));

		if (world_mouse.x > getPosition().x && world_mouse.x < getPosition().x + getSize().x &&
			world_mouse.y > getPosition().y && world_mouse.y < getPosition().y + getSize().y)
			return true;
		//ELSE
		return false;
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw((sf::RectangleShape)*this, states);
	}

	bool Button::clicked(sf::RenderWindow &win)
	{
		if (win.hasFocus())
		{
			if (!is_held)
			{
				if (aimed(win))
				{
					setFillColor(aimed_color);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						is_held = true;
						setFillColor(press_color);
					}
				}
				else
					setFillColor(idle_color);
			}
			else
			{
				if (aimed(win))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						return false;
					else
					{
						is_held = false;
						setFillColor(aimed_color);
						return true;
					}
				}
				else
				{
					if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						is_held = false;
						setFillColor(idle_color);
					}
				}
			}
		}

		return false;
	}

	Button::Button(const sf::Vector2f &position, const sf::Vector2f &size)
	{
		setPosition(position);
		setSize(size);

		idle_color = sf::Color(200, 200, 200);
		aimed_color = sf::Color(255, 255, 255);
		press_color = sf::Color(100, 100, 100);
		setFillColor(idle_color);
	}

	Button::Button(const Button &button)
	{
		is_held = button.is_held;
		idle_color = button.idle_color;
		aimed_color = button.aimed_color;
		press_color = button.press_color;
	}
}