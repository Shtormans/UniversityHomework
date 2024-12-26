#pragma once

#include "ColorChangeable.h"
#include "GameObject.h"
#include "GameObjectsContainer.h"
#include "Input.h"
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

	void create_object()
	{
		GameObject* object = new GameObject();
		object->add_component(new SelectableObject());
		object->add_component(new MovableObject());
		object->add_component(new Graphic());
		object->add_component(new ColorChangeable());
		object->add_component(new VisibilitySetter());
		object->add_component(new MouseFollower());
		object->add_component(new Retracter());

		GameObject::objectsContainer_->instantiate(object);
	}
};

