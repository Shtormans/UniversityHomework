#pragma once

#include "Input.h"
#include "SelectablesContainer.h"

class CompositeCreator : public MonoBehaviour
{
	SelectablesContainer* container_;
	bool canSelect_;

	void awake() override
	{
		canSelect_ = true;
		container_ = gameObject->get_component<SelectablesContainer>();
	}

	void update() override
	{
		if (!Input::get_key(sf::Keyboard::Num8))
		{
			container_->can_select(true);
			return;
		}

		container_->can_select(false);

		if (container_->last_selected == nullptr)
		{
			return;
		}

		if (!Input::get_mouse_button(sf::Mouse::Left))
		{
			canSelect_ = true;
			return;
		}

		if (!canSelect_)
		{
			return;
		}

		canSelect_ = false;

		SelectableObject* selectable = container_->calculate_selected();

		if (selectable == nullptr)
		{
			return;
		}

		selectable->transform->set_parent(container_->last_selected->transform);
		selectable->highlight();
	}
};

