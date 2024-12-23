#pragma once
#include "MonoBehaviour.h"
#include "SelectableObject.h"

class SelectableUser : public MonoBehaviour
{
private:
	SelectableObject* selectableObject;

protected:
	void awake() override
	{
		selectableObject = gameObject->get_component<SelectableObject>();
	}

	bool is_selected() const
	{
		return selectableObject->is_selected();
	}
};

