#pragma once

#include "SelectableUser.h"
#include "Time.h"

class MovableObject : public SelectableUser
{
private:
	float speed_;
	Graphic* graphic_;

	void awake() override
	{
		SelectableUser::awake();

		graphic_ = gameObject->get_component<Graphic>();
		speed_ = 150;
	}

	void update() override
	{
		if (!is_selected())
		{
			return;
		}

		move();
	}

	void move()
	{
		sf::Vector2f position = transform->get_position();
		sf::Vector2f direction = get_direction();

		sf::Vector2f newPosition = position + direction * speed_ * Time::get_delta_time();

		newPosition.x = Utils::repeat(newPosition.x, -graphic_->get_rect().width, Screen::get_size().x);
		newPosition.y = Utils::repeat(newPosition.y, -graphic_->get_rect().height, Screen::get_size().y);

		transform->set_position(newPosition);
	}

	sf::Vector2f get_direction()
	{
		sf::Vector2f position;

		if (Input::get_key(sf::Keyboard::Key::A))
		{
			position.x += -1;
		}

		if (Input::get_key(sf::Keyboard::Key::D))
		{
			position.x += 1;
		}

		if (Input::get_key(sf::Keyboard::Key::W))
		{
			position.y += -1;
		}

		if (Input::get_key(sf::Keyboard::Key::S))
		{
			position.y += 1;
		}

		return position;
	}
};


