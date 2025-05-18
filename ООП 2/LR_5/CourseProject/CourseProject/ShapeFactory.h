#pragma once
#include <map>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>

enum GraphicForm
{
	none = 0,
	circle = 1,
	rectangle = 2
};

class ShapeFactory
{
private:
	static ShapeFactory* instance_;
	std::map<GraphicForm, sf::Shape*> shapes_;

public:
	ShapeFactory()
	{
		if (instance_ != nullptr)
		{
			return;
		}

		instance_ = this;
	}

	~ShapeFactory()
	{
		for (const auto shape : shapes_)
		{
			delete shape.second;
		}
	}

	static sf::Shape* CreateShape(const GraphicForm form)
	{
		if (instance_->shapes_.count(form) == 0)
		{
			sf::Shape* shape = nullptr;

			switch (form) {
			case circle:
				shape = new sf::CircleShape(20.f);
				break;
			case rectangle:
				shape = new sf::RectangleShape({ 40.0f, 40.0f });
				break;
			case none:
				shape = nullptr;
				break;
			}

			instance_->shapes_[form] = shape;
			return shape;
		}

		return instance_->shapes_[form];
	}
};

