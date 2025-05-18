#pragma once
#include "GameObjectsContainer.h"
#include "Input.h"
#include "SelectableUser.h"

class Destroyer : public SelectableUser
{
	void update() override
	{
		if (!is_selected())
		{
			return;
		}

		if (Input::get_key(sf::Keyboard::M))
		{
			destroy();
		}
	}

	void destroy()
	{
		destroy_transform(transform);
	}

	void destroy_transform(const Transform* figure)
	{
		std::vector<Transform*> children;
		std::copy(figure->children_.begin(), figure->children_.end(), back_inserter(children));

		for (int i = 0; i < children.size(); i++)
		{
			Transform* child = children[i];
			destroy_transform(child);
		}

		GameObject::objectsContainer_->destroy(figure->gameObject);
	}
};

