#pragma once
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

class Screen
{
private:
	static Screen* instance_;

	sf::RenderWindow* window_;
	bool clearWindow_;

public:
	Screen(sf::RenderWindow* window)
	{
		if (instance_ != nullptr)
		{
			return;
		}

		instance_ = this;

		window_ = window;
		clearWindow_ = true;
	}

	void clear() const
	{
		if (!clearWindow_)
		{
			return;
		}

		window_->clear();
	}

	void display() const
	{
		window_->display();
	}

	static sf::RenderWindow* get_window()
	{
		return instance_->window_;
	}

	static sf::Vector2f get_size()
	{
		sf::Vector2u windowSize = instance_->window_->getSize();

		return sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
	}

	static void set_window_clear(bool value)
	{
		instance_->clearWindow_ = value;
	}

	static bool get_window_clear()
	{
		return instance_->clearWindow_;
	}
};

