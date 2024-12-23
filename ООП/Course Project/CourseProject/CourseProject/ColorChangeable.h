#pragma once

#include "SelectableUser.h"

class ColorChangeable : public SelectableUser
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

		if (Input::get_key(sf::Keyboard::Num2))
		{
			if (!canChange_)
			{
				return;
			}

			graphic_->set_random_color();
			canChange_ = false;
		}
		else
		{
			canChange_ = true;
		}
	}
};

