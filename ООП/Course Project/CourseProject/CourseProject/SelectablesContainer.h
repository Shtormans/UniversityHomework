#pragma once

#include "GameObject.h"
#include "MonoBehaviour.h"
#include "SelectableObject.h"

class SelectablesContainer : public MonoBehaviour
{
	std::vector<SelectableObject*> selectables_;
	SelectableObject* last_selected;

	void awake() override
	{
		selectables_ = GameObject::objectsContainer_->find_of_type<SelectableObject>();
	}

	void update() override
	{
		if (!Input::get_mouse_button(sf::Mouse::Left))
		{
			return;
		}

		for (auto element : selectables_)
		{
			if (element->can_select())
			{
				if (last_selected != nullptr)
				{
					last_selected->deselect();
				}

				last_selected = element;

				last_selected->select();

				return;
			}
		}
	}

public:
	SelectablesContainer() : last_selected(nullptr)
	{
	}
};

