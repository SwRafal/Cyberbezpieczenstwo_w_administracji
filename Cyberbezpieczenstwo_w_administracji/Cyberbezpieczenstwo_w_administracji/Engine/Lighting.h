#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

#define M_PI 3.14159265358979323846

namespace bu
{
	class Lighting : public sf::Drawable
	{
	private:
		sf::VertexArray vertex;

		sf::Vector2f position;
		float radius;

		unsigned int accuracy;
		sf::Color color;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void update();
	public:
		void setColor(const sf::Color& color);
		void setRadius(float radius);
		void setAccuracy(unsigned int accuracy);//Number of vertexes creating a light circle
		void setPosition(const sf::Vector2f &pos);
		void setPosition(float x, float y);
		void move(const sf::Vector2f &factor);
		void move(float factor_x, float factor_y);

		Lighting() : Lighting(sf::Vector2f(10, 10), 10, sf::Color::Yellow) {};
		Lighting(const sf::Vector2f &position, float radius, const sf::Color &color = sf::Color::Yellow, unsigned int accurary = 16);

		float getRadius() { return radius; }
		unsigned int getAccuracy() { return accuracy; }
		const sf::Color &getColor() { return color; }
	};
}