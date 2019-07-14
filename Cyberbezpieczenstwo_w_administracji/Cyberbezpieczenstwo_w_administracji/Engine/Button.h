#pragma once
#include <SFML/Graphics.hpp>

namespace gm
{
	class Button : public sf::RectangleShape
	{
	private:
		bool is_held = false;
		sf::Color idle_color; //Kolor guzika, kiedy nie jest u¿ywany
		sf::Color aimed_color;//Kolor guzika, kiedy jest namierzony
		sf::Color press_color;//Kolor guzika, kiedy jest wciœniêty
	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		void setRotation(float) = delete;
		void rotate(float) = delete;
		void scale(const sf::Vector2f&) = delete;
		void setScale(const sf::Vector2f&) = delete;
		void scale(float, float) = delete;
		void setScale(float, float) = delete;

		void setSize(float x, float y);
		void setSize(const sf::Vector2f& size) { sf::RectangleShape::setSize(size); }

		//Zmiana kolorów w zale¿noœci od akcji
		void setIdleColor(const sf::Color &color);
		void setAimedColor(const sf::Color &color);
		void setPressColor(const sf::Color &color);

		bool aimed(sf::RenderWindow &win);
		bool clicked(sf::RenderWindow &win);

		Button() : Button(sf::Vector2f(0, 0), sf::Vector2f(200, 100)) {};
		Button(const sf::Vector2f &position, const sf::Vector2f &size);
		Button(const Button &button);

		bool isHeld() { return is_held; }
		const sf::Color &getIdleColor() { return idle_color; }
		const sf::Color &getAimedColor() { return aimed_color; }
		const sf::Color &getPressColor() { return press_color; }
	};
}