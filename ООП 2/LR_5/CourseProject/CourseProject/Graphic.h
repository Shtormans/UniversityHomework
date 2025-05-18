#pragma once

#include "MonoBehaviour.h"
#include "GameObject.h"
#include "Input.h"
#include "Screen.h"
#include "ShapeFactory.h"
#include "Utils.h"

class Graphic : public MonoBehaviour
{
private:
	sf::Shape* shape_;
	sf::Color color_;
	float outlineThickness_;
	bool visible_;
	int framesWithoutCollision_;

	bool canChangeForm = true;

	void awake() override
	{
		visible_ = true;

		set_form(circle);
	}

	void update() override
	{
		if (Input::get_key(sf::Keyboard::Num1))
		{
			if (canChangeForm)
			{
				set_form((GraphicForm)Utils::randInclusive(1, 2));
			}

			canChangeForm = false;

		}
		else
		{
			canChangeForm = true;
		}

		framesWithoutCollision_++;

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
	GraphicForm form_;

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
		form_ = form;
		shape_ = ShapeFactory::CreateShape(form);

		shape_->setOutlineThickness(outlineThickness_);
	}
};

