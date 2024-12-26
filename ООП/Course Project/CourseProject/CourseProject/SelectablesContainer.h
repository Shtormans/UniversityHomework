#pragma once

#include "GameObject.h"
#include "MonoBehaviour.h"
#include "SelectableObject.h"
#include "GameObjectsContainer.h"

class SelectablesContainer : public MonoBehaviour
{
	std::vector<SelectableObject*> selectables_;
	bool can_select_;

	void awake() override
	{
		can_select_ = true;
	}

	void update() override
	{
		selectables_ = GameObject::objectsContainer_->find_of_type<SelectableObject>();

		if (!can_select_)
		{
			return;
		}

		if (!Input::get_mouse_button(sf::Mouse::Left))
		{
			return;
		}

		SelectableObject* selected = calculate_selected();
		if (selected != nullptr)
		{
			if (last_selected != nullptr)
			{
				last_selected->deselect();
			}

			last_selected = selected;

			last_selected->select();
		}
	}

public:
	SelectableObject* last_selected;

	SelectablesContainer() : last_selected(nullptr)
	{
	}

	void can_select(const bool value)
	{
		can_select_ = value;
	}

	SelectableObject* calculate_selected() const
	{
		for (auto element : selectables_)
		{
			if (element->can_select())
			{
				SelectableObject* toSelect = element;
				while (toSelect->transform->parent_ != nullptr)
				{
					toSelect = toSelect->transform->parent_->gameObject->get_component<SelectableObject>();
				}

				return toSelect;
			}
		}

		return nullptr;
	}
};

