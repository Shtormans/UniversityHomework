#pragma once

#include "GameObject.h"
#include "Graphic.h"
#include "Input.h"
#include "MonoBehaviour.h"

class SelectableObject : public MonoBehaviour
{
private:
	const float selectedThickness = 2;
	const float deselectedThickness = 0;

	Graphic* graphic_;
	bool selected;

	void awake() override
	{
		graphic_ = gameObject->get_component<Graphic>();
	}

public:
	bool can_select()
	{
		if (selected)
		{
			return false;
		}

		if (graphic_->collides(Input::get_mouse_position()))
		{
			select();
			return true;
		}

		return false;
	}

	void select()
	{
		graphic_->set_outline(selectedThickness);

		selected = true;
	}

	void highlight() const
	{
		graphic_->set_visibility(true);
	}

	void unhighlight() const
	{
		graphic_->set_visibility(false);
	}

	void deselect()
	{
		graphic_->set_outline(deselectedThickness);

		selected = false;
	}

	bool is_selected() const
	{
		return selected;
	}
};

