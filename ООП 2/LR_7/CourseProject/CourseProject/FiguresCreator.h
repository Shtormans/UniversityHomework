#pragma once

#include "GameObject.h"
#include "GameObjectsContainer.h"
#include "Graphic.h"
#include "Input.h"
#include "MonoBehaviour.h"
#include "TargetFollower.h"

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
		object->add_component(new TargetFollower());

		GameObject::objectsContainer_->instantiate(object);

		object->id = Utils::randInclusive(0, 99999);

		return object;
	}
};

