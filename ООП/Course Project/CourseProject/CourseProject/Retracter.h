#pragma once

#include "SelectableUser.h"
#include "Input.h"

class Retracter : public SelectableUser
{
	bool canRetract;

	sf::Vector2f startPosition_;
	sf::Color startColor_;

	Graphic* graphic_;

	void awake() override
	{
		SelectableUser::awake();

		canRetract = true;

		graphic_ = gameObject->get_component<Graphic>();
	}

	void update() override
	{
		if (!is_selected())
		{
			return;
		}

		if (Input::get_key(sf::Keyboard::Num5))
		{
			if (!canRetract)
			{
				return;
			}

			transform->set_position(startPosition_);
			graphic_->set_color(startColor_);

			canRetract = false;
		}
		else
		{
			canRetract = true;
		}
	}

public:
	void memorize_data()
	{
		startPosition_ = transform->get_position();
		startColor_ = graphic_->get_color();
	}
};

