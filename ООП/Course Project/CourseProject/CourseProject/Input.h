#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Input
{
private:
	static Input* instance_;

	sf::RenderWindow* window_;

public:
	Input(sf::RenderWindow* window)
	{
		if (instance_ != nullptr)
		{
			return;
		}

		instance_ = this;
		window_ = window;
	}

	static bool get_key(const sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}

	static bool get_mouse_button(const sf::Mouse::Button button)
	{
		return sf::Mouse::isButtonPressed(button);
	}

	static sf::Vector2f get_mouse_position()
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*instance_->window_);

		return sf::Vector2f(mousePosition.x, mousePosition.y);
	}
};

