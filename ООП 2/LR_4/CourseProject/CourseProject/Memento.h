#pragma once

#include <SFML/Graphics/Color.hpp>

#include "FigureData.h"
#include "GameObject.h"
#include "Graphic.h"
#include "MonoBehaviour.h"

class Graphic;

class Memento : public MonoBehaviour
{
public:
	FigureData save() const
	{
		int id = gameObject->id;
		sf::Vector2f position = transform->get_position();
		sf::Color color = gameObject->get_component<Graphic>()->get_color();
		GraphicForm form = gameObject->get_component<Graphic>()->form_;

		std::vector<FigureData> children;
		children.reserve(transform->children_.size());

		for (Transform* child : transform->children_)
		{
			children.push_back(child->gameObject->get_component<Memento>()->save());
		}

		FigureData data
		{
			id,
			position,
			color,
			form,
			children
		};

		return data;
	}

	void load(const FigureData& data, bool withoutId = false) const
	{
		if (!withoutId)
		{
			gameObject->id = data.Id;
		}

		gameObject->transform->set_position(data.Position);
		gameObject->get_component<Graphic>()->set_color(data.Color);
		gameObject->get_component<Graphic>()->set_form(data.Form);
	}
};
