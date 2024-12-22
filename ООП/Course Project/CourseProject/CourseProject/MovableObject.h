#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "GameObject.h"
#include "Time.h"

class MovableObject : public GameObject
{
private:
	float speed_;
	sf::CircleShape* shape_;

	void awake() override
	{
		speed_ = 80;

		shape_ = new sf::CircleShape(20.f);
		shape_->setFillColor(sf::Color::Green);
	}

	void update(sf::RenderWindow* window) override
	{
		move();

		window->draw(*shape_, *transform);
	}

	void on_destroy() override
	{
		delete shape_;
	}

	void move()
	{
		sf::Vector2f position = transform->get_local_position();
		sf::Vector2f direction = get_direction();

		sf::Vector2f newPosition = position + direction * speed_ * Time::get_delta_time();

		transform->set_local_position(newPosition);
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


