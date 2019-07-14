#include "Information.h"

namespace gm
{
	void Information::adjust_text()
	{
		sf::String str = txt_str;
		int last_space = 0;

		if (!str.isEmpty())
		{
			for (int i = 0; i < str.getSize(); i++)
			{
				if (str[i] == ' ')
					last_space = i;
				text.setString(str.substring(0, i + 1));

				if (text.getLocalBounds().width > getSize().x)
				{
					str[last_space] = '\n';
				}
			}
		}
	}

	void Information::setSize(const sf::Vector2f & size)
	{
		sf::RectangleShape::setSize(size);
		adjust_text();
	}

	void Information::setSize(float x, float y)
	{
		setSize(sf::Vector2f(x, y));
	}

	void Information::setPosition(const sf::Vector2f &position)
	{
		sf::RectangleShape::setPosition(position);
		text.setPosition(position);
	}

	void Information::setPosition(float x, float y)
	{
		sf::RectangleShape::setPosition(x, y);
		text.setPosition(x, y);
	}

	void Information::move(const sf::Vector2f &offset)
	{
		sf::RectangleShape::move(offset);
		text.move(offset);
	}

	void Information::move(float offsetX, float offsetY)
	{
		sf::RectangleShape::move(offsetX, offsetY);
		text.move(offsetX, offsetY);
	}

	void Information::setTextFont(sf::Font& font)
	{
		text.setFont(font);
		adjust_text();
	}

	void Information::setTextColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	void Information::setTextString(sf::String str)
	{
		txt_str = str;
		text.setString(str);
		adjust_text();
	}

	void Information::setTextSize(unsigned int size)
	{
		text.setCharacterSize(size);
		adjust_text();
	}

	/*Draw i konstruktory*/
	void Information::draw(sf::RenderWindow &win)
	{
		win.draw((sf::RectangleShape)(*this));
		win.draw(text);
	}

	Information::Information(sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, unsigned int font_size)
	{
		text.setFont(font);
		setPosition(position);
		setSize(size);
		text.setCharacterSize(font_size);
	}

	Information::Information(const Information &info)
		: sf::RectangleShape(info)
	{
		text.setFont(*(info.text.getFont()));
		text.setCharacterSize(info.text.getCharacterSize());
		text.setFillColor(info.text.getFillColor());

		setSize(info.getSize());
		setPosition(info.getPosition());
	}

	Information::~Information()
	{
	}
}