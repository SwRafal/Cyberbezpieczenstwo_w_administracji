#pragma once
#include "Button.h"

namespace gm
{
	/*Horizontal slider*/
	class SliderH : public sf::Drawable
	{
	private:
		int min_v;
		int max_v;
		int val;

		sf::RectangleShape splint;
		Button button;
		//Dopasowanie
		void adjust_button();
	public:
		//Mechanika
		bool splint_aimed(sf::RenderWindow &win);

		void setMinValue(int value);
		void setMaxValue(int value);
		void setValue(int value);

		//Ca³oœæ suwaka
		void setSize(const sf::Vector2f &size);
		void setSize(float length, float height);
		void setPosition(const sf::Vector2f &position);
		void setPosition(float x, float y);
		void move(const sf::Vector2f &offset);
		void move(float offsetX, float offsetY);

		//Kolor szyny
		void setSplintColor(const sf::Color &color);
		void setSplintTexture(const sf::Texture* texture);

		//Zmiana kolorów guzika
		void setIdleColor(const sf::Color &color);
		void setAimedColor(const sf::Color &color);
		void setPressColor(const sf::Color &color);
		void setButtonTexture(const sf::Texture* texture);

		//Ogólne
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::RenderWindow &win);

		//Gettery
		int getValue() { return val; }
		const sf::Texture* getSplintTexture() { return splint.getTexture(); }
		const sf::Texture* getButtonTexture() { return button.getTexture(); }

		SliderH() : SliderH(sf::Vector2f(0, 0), 200, 50) {};
		SliderH(const sf::Vector2f &position, float lenght, float height, int min_value = 0, int max_value = 100, int val = 0);
		~SliderH() {};
	};
}