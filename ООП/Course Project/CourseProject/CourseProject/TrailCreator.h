#pragma once
#include "Input.h"
#include "MonoBehaviour.h"
#include "Screen.h"

class TrailCreator : public MonoBehaviour
{
	bool canChange_;

	void awake() override
	{
		canChange_ = true;
	}

	void update() override
	{
		if (Input::get_key(sf::Keyboard::Num1))
		{
			if (!canChange_)
			{
				return;
			}

			Screen::set_window_clear(!Screen::get_window_clear());
			canChange_ = false;
		}
		else
		{
			canChange_ = true;
		}
	}
};

