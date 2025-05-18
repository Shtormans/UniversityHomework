#pragma once

#include "GameObject.h"
#include "GameObjectsContainer.h"
#include "Graphic.h"
#include "Input.h"
#include "MonoBehaviour.h"

class FiguresCreator : public MonoBehaviour
{
	bool canAdd_;

	void awake() override
	{
		canAdd_ = true;
	}

	void update() override
	{
		if (Input::get_key(sf::Keyboard::Num0))
		{
			if (!canAdd_)
			{
				return;
			}

			canAdd_ = false;

			create_object();
		}
		else
		{
			canAdd_ = true;
		}
	}

public:
	GameObject* create_object()
	{
		GameObject* object = new GameObject();
		object->add_component(new Graphic());

		GameObject::objectsContainer_->instantiate(object);

		object->id = Utils::randInclusive(0, 99999);

		sf::Vector2f screenSize = Screen::get_size();
		float x = Utils::randInclusive(0, screenSize.x);
		float y = Utils::randInclusive(0, screenSize.y);

		object->transform->set_position(sf::Vector2f(x, y));

		return object;
	}
};

