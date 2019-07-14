#include "SliderV.h"

namespace bu
{
	void SliderV::adjust_button()
	{
		button.setSize(splint.getSize().x, splint.getSize().y * 1.f / (max_v - min_v + 1));
		button.setPosition(splint.getPosition().x, splint.getPosition().y + button.getSize().y*(val - min_v));
	}

	bool SliderV::splint_aimed(sf::RenderWindow &win)
	{
		if (sf::Mouse::getPosition(win).x > splint.getPosition().x && sf::Mouse::getPosition(win).x < splint.getPosition().x + splint.getSize().x &&
			sf::Mouse::getPosition(win).y > splint.getPosition().y && sf::Mouse::getPosition(win).y < splint.getPosition().y + splint.getSize().y)
			return true;
		else
			return false;
	}

	//Mechanika
	void SliderV::setMinValue(int value)
	{
		if (value > max_v)
			max_v = value + 1;

		min_v = value;

		setValue(getValue());
		adjust_button();
	}

	void SliderV::setMaxValue(int value)
	{
		if (value < min_v)
			min_v = value - 1;

		max_v = value;

		setValue(getValue());
		adjust_button();
	}

	void SliderV::setValue(int value)
	{
		if (value < min_v)
			val = min_v;
		else if (value > max_v)
			val = max_v;
		else
			val = value;
	}

	//Ogólne
	void SliderV::setSize(const sf::Vector2f &size)
	{
		splint.setSize(size);
		adjust_button();
	}

	void SliderV::setSize(float length, float width)
	{
		splint.setSize(sf::Vector2f(width, length));
		adjust_button();
	}

	void SliderV::setPosition(const sf::Vector2f &position)
	{
		splint.setPosition(position);
		adjust_button();
	}

	void SliderV::setPosition(float x, float y)
	{
		splint.setPosition(x, y);
		adjust_button();
	}

	void SliderV::move(const sf::Vector2f &offset)
	{
		splint.move(offset);
		button.move(offset);
	}

	void SliderV::move(float offsetX, float offsetY)
	{
		splint.move(offsetX, offsetY);
		button.move(offsetX, offsetY);
	}

	//Kolor szyny
	void SliderV::setSplintColor(const sf::Color &color)
	{
		splint.setFillColor(color);
	}
	void SliderV::setSplintTexture(const sf::Texture* texture)
	{
		splint.setTexture(texture);
	}

	//Zmiana kolorów guzika
	void SliderV::setIdleColor(const sf::Color &color)
	{
		button.setIdleColor(color);
	}

	void SliderV::setAimedColor(const sf::Color &color)
	{
		button.setAimedColor(color);
	}

	void SliderV::setPressColor(const sf::Color &color)
	{
		button.setPressColor(color);
	}
	void SliderV::setButtonTexture(const sf::Texture* texture)
	{
		button.setTexture(texture);
	}

	//Ogólne
	void SliderV::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(splint, states);
		target.draw(button, states);
	}

	void SliderV::update(sf::RenderWindow &win)
	{
		button.clicked(win);//Mechanizm dzia³ania guzika
		if (button.isHeld() || (splint_aimed(win) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		{
			while (sf::Mouse::getPosition(win).y < button.getPosition().y && val > min_v)
			{
				val--;
				adjust_button();
			}		
			while(sf::Mouse::getPosition(win).y > button.getPosition().y + button.getSize().y && val < max_v)
			{
				val++;
				adjust_button();
			}
		}
	}

	SliderV::SliderV(const sf::Vector2f &position, float lenght, float width, int min_value, int max_value, int value)
	{
		splint.setPosition(position);
		splint.setSize(sf::Vector2f(width, lenght));
		setMinValue(min_value);
		setMaxValue(max_value);
		setValue(value);

		setSplintColor(sf::Color::Red);

		adjust_button();
	}
}