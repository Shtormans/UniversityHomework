#pragma once

#include "SelectableUser.h"

class VisibilitySetter : public SelectableUser
{
	Graphic* graphic_;
	bool canChange_;

	void awake() override
	{
		SelectableUser::awake();

		canChange_ = true;
		graphic_ = gameObject->get_component<Graphic>();
	}

	void update() override
	{
		if (!is_selected())
		{
			return;
		}

		if (Input::get_key(sf::Keyboard::Num3))
		{
			if (!canChange_)
			{
				return;
			}

			graphic_->set_visibility(!graphic_->get_visibility());
			canChange_ = false;
		}
		else
		{
			canChange_ = true;
		}
	}
};

