#include "TextField.h"

namespace gm
{
	void TextField::setActive(bool active)
	{
		if (active)
			is_active = true;
		else
			is_active = false;
	}

	void TextField::switchStatus()
	{
		is_active = !is_active;
	}

	void TextField::setLimit(bool on, unsigned short limit)
	{
		hasLimit = on;
		this->limit = limit;
	}

	void TextField::setLimit(bool on)
	{
		hasLimit = on;
	}

	void TextField::update(sf::RenderWindow &win, sf::Uint32 char_entered)
	{
		if (clicked(win) && win.hasFocus())
			is_active = true;

		if (is_active)
		{
			setFillColor(getPressColor());
			if (!hasLimit || (hasLimit && getTextString().getSize() < limit))
			{
				if ((char_entered >= 32 && char_entered <= 126) || char_entered == 243 || char_entered == 322 || char_entered == 380 || char_entered == 243 || char_entered == 281 || char_entered == 347)
				{
					setTextString(getTextString() + static_cast<wchar_t>(char_entered));
				}
			}
			if (char_entered == BACKSPACE && !getTextString().toAnsiString().empty())//Backspace
				setTextString(getTextString().toAnsiString().substr(0, getTextString().toAnsiString().length() - 1));
			else if (char_entered == ENTER)
				is_active = false;

			if (!aimed(win) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				is_active = false;
		}
	}

	TextField::TextField(sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, unsigned int font_size)
		:TextButton(font,position,size,font_size)
	{
		is_active = false;
		hasLimit = false;
		limit = 20;
	}

	TextField::~TextField() {};
}