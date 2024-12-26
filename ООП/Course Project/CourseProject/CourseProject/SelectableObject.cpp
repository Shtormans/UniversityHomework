#include "SelectableObject.h"

#include "Retracter.h"
#include "GameObject.h"
#include "Input.h"

void SelectableObject::awake()
{
	graphic_ = gameObject->get_component<Graphic>();
	retracter_ = gameObject->get_component<Retracter>();
}

bool SelectableObject::can_select()
{
	if (selected)
	{
		return false;
	}

	if (graphic_->collides(Input::get_mouse_position()))
	{
		return true;
	}

	return false;
}

void SelectableObject::select()
{
	highlight();
	retracter_->memorize_data();

	selected = true;
}

void SelectableObject::highlight() const
{
	graphic_->set_outline(selectedThickness);
}

void SelectableObject::unhighlight() const
{
	graphic_->set_outline(deselectedThickness);
}

void SelectableObject::deselect()
{
	unhighlight();

	selected = false;
}

bool SelectableObject::is_selected() const
{
	return selected;
}