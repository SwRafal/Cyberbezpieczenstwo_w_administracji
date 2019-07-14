#include "SliderH.h"
#include <iostream>

namespace bu
{
	void SliderH::adjust_button()
	{
		button.setSize(splint.getSize().x / (max_v - min_v + 1), splint.getSize().y);
		button.setPosition(splint.getPosition().x + button.getSize().x*(val - min_v), splint.getPosition().y);
	}

	bool SliderH::splint_aimed(sf::RenderWindow &win)
	{
		if (sf::Mouse::getPosition(win).x > splint.getPosition().x && sf::Mouse::getPosition(win).x < splint.getPosition().x + splint.getSize().x &&
			sf::Mouse::getPosition(win).y > splint.getPosition().y && sf::Mouse::getPosition(win).y < splint.getPosition().y + splint.getSize().y)
			return true;
		else
			return false;
	}

	//Mechanika
	void SliderH::setMinValue(int value)
	{
		if (value > max_v)
			max_v = value+1;

		min_v = value;

		setValue(getValue());
		adjust_button();
	}

	void SliderH::setMaxValue(int value)
	{
		if (value < min_v)
			min_v = value-1;
		
		max_v = value;

		setValue(getValue());
		adjust_button();
	}

	void SliderH::setValue(int value)
	{
		if (value < min_v)
			val = min_v;
		else if (value > max_v)
			val = max_v;
		else
			val = value;
	}

	//Ogólne
	void SliderH::setSize(const sf::Vector2f &size)
	{
		splint.setSize(size);
		adjust_button();
	}

	void SliderH::setSize(float length, float height)
	{
		splint.setSize(sf::Vector2f(length, height));
		adjust_button();
	}

	void SliderH::setPosition(const sf::Vector2f &position)
	{
		splint.setPosition(position);
		adjust_button();
	}

	void SliderH::setPosition(float x, float y)
	{
		splint.setPosition(x, y);
		adjust_button();
	}

	void SliderH::move(const sf::Vector2f &offset)
	{
		splint.move(offset);
		button.move(offset);
	}

	void SliderH::move(float offsetX, float offsetY)
	{
		splint.move(offsetX, offsetY);
		button.move(offsetX, offsetY);
	}

	//Kolor szyny
	void SliderH::setSplintColor(const sf::Color &color)
	{
		splint.setFillColor(color);
	}
	void SliderH::setSplintTexture(const sf::Texture* texture)
	{
		splint.setTexture(texture);
	}

	//Zmiana kolorów guzika
	void SliderH::setIdleColor(const sf::Color &color)
	{
		button.setIdleColor(color);
	}

	void SliderH::setAimedColor(const sf::Color &color)
	{
		button.setAimedColor(color);
	}

	void SliderH::setPressColor(const sf::Color &color)
	{
		button.setPressColor(color);
	}
	void SliderH::setButtonTexture(const sf::Texture* texture)
	{
		button.setTexture(texture);
	}

	//Ogólne
	void SliderH::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(splint, states);
		target.draw(button, states);
	}

	void SliderH::update(sf::RenderWindow &win)
	{
		button.clicked(win);//Mechanizm dzia³ania guzika
		if (button.isHeld() || (splint_aimed(win) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		{
			while (sf::Mouse::getPosition(win).x < button.getPosition().x && val > min_v)
			{
				val--;
				adjust_button();
			}
			while (sf::Mouse::getPosition(win).x > button.getPosition().x + button.getSize().x && val < max_v)
			{
				val++;
				adjust_button();
			}
		}
	}

	SliderH::SliderH(const sf::Vector2f &position, float length, float height, int min_value, int max_value, int value)
	{
		splint.setPosition(position);
		splint.setSize(sf::Vector2f(length, height));
		setMinValue(min_value);
		setMaxValue(max_value);
		setValue(value);

		setSplintColor(sf::Color::Red);

		adjust_button();
	}
}