#pragma once

#include "ColorChangeable.h"
#include "Destroyer.h"
#include "GameObject.h"
#include "GameObjectsContainer.h"
#include "Input.h"
#include "Memento.h"
#include "MonoBehaviour.h"
#include "MouseFollower.h"
#include "MovableObject.h"
#include "Retracter.h"
#include "VisibilitySetter.h"

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
		object->add_component(new SelectableObject());
		object->add_component(new MovableObject());
		object->add_component(new Graphic());
		object->add_component(new ColorChangeable());
		object->add_component(new VisibilitySetter());
		object->add_component(new MouseFollower());
		object->add_component(new Retracter());
		object->add_component(new Memento());
		object->add_component(new Destroyer());

		GameObject::objectsContainer_->instantiate(object);

		object->id = Utils::randInclusive(0, 99999);

		return object;
	}
};

