#include "CheckBox.h"

namespace bu
{
	void CheckBox::adjust_x()
	{
		if (_x->getFont() == nullptr || _x->getString().isEmpty())
			return;
		while (_x->getLocalBounds().height < getSize().y)
			_x->setCharacterSize(_x->getCharacterSize()+1);
		while(_x->getLocalBounds().height > getSize().y)
			_x->setCharacterSize(_x->getCharacterSize() - 1);

		sf::Vector2f position;
		position.x = getPosition().x + getSize().x/2.f - _x->getLocalBounds().width/2.f - _x->getLocalBounds().left;
		position.y = getPosition().y + getSize().y/2.f - _x->getLocalBounds().height/2.f - _x->getLocalBounds().top;

		_x->setPosition(position);
	}

	void CheckBox::setCheckFlag(bool flag)
	{
		is_checked = flag;
	}

	void CheckBox::setPosition(const sf::Vector2f &pos)
	{
		Button::setPosition(pos);
		adjust_x();
	}
	void CheckBox::setPosition(float x, float y)
	{
		Button::setPosition(x, y);
		adjust_x();
	}

	void CheckBox::setSize(const sf::Vector2f &size)
	{
		Button::setSize(size);
		adjust_x();
	}
	void CheckBox::setSize(float x, float y)
	{
		Button::setSize(sf::Vector2f(x, y));
		adjust_x();
	}

	void CheckBox::setIdleCheckColor(const sf::Color &color)
	{
		idle_check_color = color;
	}
	void CheckBox::setAimedCheckColor(const sf::Color &color)
	{
		aimed_check_color = color;
	}
	void CheckBox::setPressCheckColor(const sf::Color &color)
	{
		press_check_color = color;
	}

	/*Main methods*/
	void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sf::RectangleShape(*this));
		if (is_checked)
			target.draw(*_x);
	}
	void CheckBox::update(sf::RenderWindow &win)
	{
		if (Button::clicked(win))
			is_checked = !is_checked;

		if (win.hasFocus())
		{
			if (isHeld())
				_x->setFillColor(press_check_color);
			else if (aimed(win))
				_x->setFillColor(aimed_check_color);
			else
				_x->setFillColor(idle_check_color);
		}
	}

	/*Constructors*/
	CheckBox::CheckBox(const sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, bool checkFlag) : Button::Button(position, size)
	{
		is_checked = checkFlag;

		idle_check_color = sf::Color(100, 100, 100);
		aimed_check_color = sf::Color(150, 150, 150);
		press_check_color = sf::Color(25, 25, 25);

		_x = new sf::Text("X", font);
		_x->setFillColor(idle_check_color);
		_x->setCharacterSize(size.y);
		adjust_x();
	}
	CheckBox::CheckBox(const CheckBox &checkbox)
	{
		Button::Button(Button(*this));
		is_checked = checkbox.is_checked;

		idle_check_color = checkbox.idle_check_color;
		aimed_check_color = checkbox.aimed_check_color;
		press_check_color = checkbox.press_check_color;
		_x = checkbox._x;
	}
	CheckBox::~CheckBox()
	{
		delete _x;
		_x = nullptr;
	}
}