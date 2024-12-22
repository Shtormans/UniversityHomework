#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Screen
{
private:
	static Screen* instance_;

	sf::RenderWindow* window_;

public:
	Screen(sf::RenderWindow* window)
	{
		if (instance_ != nullptr)
		{
			return;
		}

		instance_ = this;
		window_ = window;
	}

	sf::Vector2f get_size() const
	{
		sf::Vector2u windowSize = window_->getSize();

		return sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
	}
};

