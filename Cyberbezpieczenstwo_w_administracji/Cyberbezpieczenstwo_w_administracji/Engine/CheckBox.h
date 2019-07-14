#pragma once
#include "Button.h"

namespace gm
{
	class CheckBox : public Button
	{
	private:
		bool is_checked;
		sf::Color idle_check_color; //Kolor guzika, kiedy nie jest u¿ywany
		sf::Color aimed_check_color;//Kolor guzika, kiedy jest namierzony
		sf::Color press_check_color;//Kolor guzika, kiedy jest wciœniêty
		sf::Text *_x = nullptr;
	public:
		void adjust_x();
		void setCheckFlag(bool flag);
		void setPosition(const sf::Vector2f &pos);
		void setPosition(float x, float y);
		void setSize(const sf::Vector2f &size);
		void setSize(float x, float y);

		void setIdleCheckColor(const sf::Color &color);
		void setAimedCheckColor(const sf::Color &color);
		void setPressCheckColor(const sf::Color &color);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::RenderWindow &win);
		bool clicked(sf::RenderWindow &win) = delete;

		CheckBox(sf::Font &font) : CheckBox(font,sf::Vector2f(0, 0), sf::Vector2f(200, 100)) {};
		CheckBox(const sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, bool checkFlag = false);
		CheckBox(const CheckBox &checkbox);
		~CheckBox();

		bool isChecked() { return is_checked; }
		const sf::Color &getCheckColor() { return _x->getFillColor(); }
		const sf::Color &getIdleCheckColor() { return idle_check_color; }
		const sf::Color &getAimedCheckColor() { return aimed_check_color; }
		const sf::Color &getPressCheckColor() { return press_check_color; }
	};
}