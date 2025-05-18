#pragma once

#include "SelectableUser.h"

class MouseFollower : public SelectableUser
{
	std::vector<sf::Vector2f> trajectory_;
	bool moving;
	int trajectoryIndex;

	void update() override
	{
		if (!is_selected())
		{
			return;
		}

		if (moving)
		{
			move_by_trajectory();
			return;
		}

		if (Input::get_key(sf::Keyboard::Num4))
		{
			trajectory_.push_back(Input::get_mouse_position());
		}
		else
		{
			if (!trajectory_.empty())
			{
				moving = true;
			}
		}
	}

	void move_by_trajectory()
	{
		if (trajectoryIndex >= trajectory_.size())
		{
			moving = false;
			trajectoryIndex = 0;
			trajectory_.clear();
			
			return;
		}

		transform->set_position(trajectory_[trajectoryIndex]);
		trajectoryIndex++;
	}
};

