#pragma once

#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "MonoBehaviour.h"
#include "Screen.h"
#include "Utils.h"

enum GraphicForm
{
	none = 0,
	circle = 1,
	rectangle = 2
};

class Graphic : public MonoBehaviour
{
private:
	sf::Shape* shape_;
	sf::Color color_;
	float outlineThickness_;
	bool visible_;
	GraphicForm form_;
	int framesWithoutCollision_;

	void awake() override
	{
		visible_ = true;

		set_form(circle);
		set_color(sf::Color::Green);
	}

	void update() override
	{
		framesWithoutCollision_++;

		if (!visible_)
		{
			return;
		}

		Screen::get_window()->draw(*shape_, *transform);
	}

	void on_collision_stay(GameObject* other) override
	{
		if (framesWithoutCollision_ > 1)
		{
			set_form(static_cast<GraphicForm>(form_ % 2 + 1));
		}

		framesWithoutCollision_ = 0;
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

	bool collides(sf::FloatRect other) const
	{
		return get_rect().intersects(other);
	}

	void set_outline(const float thickness)
	{
		shape_->setOutlineThickness(thickness);
		outlineThickness_ = thickness;

		for (auto child : transform->children_)
		{
			Graphic* graphic = child->gameObject->get_component<Graphic>();

			if (graphic != nullptr)
			{
				graphic->set_outline(thickness);
			}
		}
	}

	void set_random_color()
	{
		int r = Utils::randInclusive(0, 255);
		int g = Utils::randInclusive(0, 255);
		int b = Utils::randInclusive(0, 255);

		color_ = sf::Color(r, g, b, 255);
		shape_->setFillColor(color_);

		for (auto child : transform->children_)
		{
			Graphic* graphic = child->gameObject->get_component<Graphic>();

			if (graphic != nullptr)
			{
				graphic->set_random_color();
			}
		}
	}

	void set_color(const sf::Color color)
	{
		shape_->setFillColor(color);
		color_ = color;
	}

	sf::Color get_color() const
	{
		return shape_->getFillColor();
	}

	void set_visibility(const bool value)
	{
		visible_ = value;

		for (auto child : transform->children_)
		{
			Graphic* graphic = child->gameObject->get_component<Graphic>();

			if (graphic != nullptr)
			{
				graphic->set_visibility(value);
			}
		}
	}

	bool get_visibility() const
	{
		return visible_;
	}

	void set_form(GraphicForm form)
	{
		if (form_ != none)
		{
			delete shape_;
		}

		form_ = form;

		switch (form) {
		case circle:
			shape_ = new sf::CircleShape(20.f);
			break;
		case rectangle:
			shape_ = new sf::RectangleShape({ 40.0f, 40.0f });
			break;
		case none:
			shape_ = nullptr;
			break;
		}

		set_color(color_);
		shape_->setOutlineThickness(outlineThickness_);
	}
};

