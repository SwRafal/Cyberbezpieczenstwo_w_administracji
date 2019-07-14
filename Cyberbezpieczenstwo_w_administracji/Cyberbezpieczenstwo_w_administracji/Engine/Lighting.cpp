#include "Lighting.h"

namespace gm
{
	void Lighting::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(vertex);
	}

	void Lighting::update()
	{
		vertex.resize(accuracy+2);
		vertex[0].position = this->position;

		double angle = 2*M_PI / ((double)accuracy);

		for (int i = 1; i < vertex.getVertexCount(); i++)
		{
			vertex[i].position.x = vertex[0].position.x + this->radius*sin(i*angle);
			vertex[i].position.y = vertex[0].position.y - this->radius*cos(i*angle);
		}
	}

	void Lighting::setColor(const sf::Color& color)
	{
		this->color = color;
		
		vertex[0].color = this->color;
		for (int i = 1; i < vertex.getVertexCount(); i++)
		{
			vertex[i].color = sf::Color(this->color.r, this->color.g, this->color.b, 1);
		}
	}

	void Lighting::setRadius(float radius)
	{
		if (radius <10)
			this->radius = 10;
		else
			this->radius = radius;
		update();
	}

	void Lighting::setAccuracy(unsigned int accuracy)
	{
		if (accuracy < 8)
			this->accuracy = 8;
		else if (accuracy % 2 != 0)
			this->accuracy = accuracy + 1;
		else
			this->accuracy = accuracy;

		update();
	}

	void Lighting::setPosition(const sf::Vector2f &pos)
	{
		position = pos;
		update();
	}

	void Lighting::setPosition(float x, float y)
	{
		this->position.x = x;
		this->position.y = y;

		update();
	}

	void Lighting::move(const sf::Vector2f &factor)
	{
		for (int i = 0; i < vertex.getVertexCount(); i++)
		{
			vertex[i].position = vertex[i].position + factor;
		}
	}

	void Lighting::move(float factor_x, float factor_y)
	{
		for (int i = 0; i < vertex.getVertexCount(); i++)
		{
			vertex[i].position.x = vertex[i].position.x + factor_x;
			vertex[i].position.y = vertex[i].position.y + factor_y;
		}
	}

	Lighting::Lighting(const sf::Vector2f &position, float radius, const sf::Color &color, unsigned int accuracy)
	{
		vertex.setPrimitiveType(sf::TriangleFan);

		if (accuracy < 8)
			this->accuracy = 8;
		else if (accuracy % 2 != 0)
			this->accuracy = accuracy + 1;
		else
			this->accuracy = accuracy;

		this->position = position;
		this->radius = radius;
		this->color = color;

		update();
	}
}