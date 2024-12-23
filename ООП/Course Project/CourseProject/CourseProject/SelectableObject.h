#pragma once

#include "GameObject.h"
#include "Graphic.h"
#include "Input.h"
#include "MonoBehaviour.h"

class SelectableObject : public MonoBehaviour
{
private:
	Graphic* graphic_;
	bool selected;

	void awake() override
	{
		graphic_ = gameObject->get_component<Graphic>();
	}

	void select()
	{
		graphic_->set_outline(2);

		selected = true;
	}


public:
	bool try_select()
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

	void deselect()
	{
		graphic_->set_outline(0);

		selected = false;
	}

	bool is_selected() const
	{
		return selected;
	}
};

