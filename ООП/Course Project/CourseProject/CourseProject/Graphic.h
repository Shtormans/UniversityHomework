#pragma once

#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>

#include "MonoBehaviour.h"
#include "Screen.h"
#include "Utils.h"

class Graphic : public MonoBehaviour
{
private:
	sf::CircleShape* shape_;
	bool visible_;

	void awake() override
	{
		visible_ = true;

		shape_ = new sf::CircleShape(20.f);
		shape_->setFillColor(sf::Color::Green);
	}

	void update() override
	{
		if (!visible_)
		{
			return;
		}

		Screen::get_window()->draw(*shape_, *transform);
	}

	void on_destroy() override
	{
		delete shape_;
	}

	sf::Shape* get_shape() const
	{
		return shape_;
	}
public:
	sf::FloatRect get_rect() const
	{
		sf::FloatRect rect = shape_->getGlobalBounds();

		rect.left = transform->get_position().x;
		rect.top = transform->get_position().y;

		return rect;
	}

	bool collides(const sf::Vector2f position) const
	{
		return get_rect().contains(position.x, position.y);
	}

	void set_outline(const float thickness) const
	{
		shape_->setOutlineThickness(thickness);
	}

	void set_random_color() const
	{
		int r = Utils::randInclusive(0, 255);
		int g= Utils::randInclusive(0, 255);
		int b = Utils::randInclusive(0, 255);

		shape_->setFillColor(sf::Color(r, g, b, 255));
	}

	void set_visibility(const bool value)
	{
		visible_ = value;
	}

	bool get_visibility() const
	{
		return visible_;
	}
};

