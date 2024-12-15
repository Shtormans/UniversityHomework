#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class EventManager
{
private:
	static EventManager* instance_;

	sf::RenderWindow* window_;

	std::vector<sf::Event> events_;

	std::vector<sf::Event::KeyEvent> down_keys_;
	std::vector<sf::Event::KeyEvent> up_keys_;
	std::vector<sf::Event::KeyEvent> pressed_keys_;

	void try_set_down_key(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyReleased)
			return;

		down_keys_.push_back(event.key);
		pressed_keys_.erase(std::remove(pressed_keys_.begin(), pressed_keys_.end(), event.key), pressed_keys_.end());
	}

	void try_set_up_key(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed)
			return;

		up_keys_.push_back(event.key);
		pressed_keys_.push_back(event.key);
	}

public:
	EventManager(sf::RenderWindow* window)
	{
		if (instance_ != nullptr)
		{
			return;
		}

		instance_ = this;
		window_ = window;
	}

	void UpdateEvents()
	{
		events_.clear();
		down_keys_.clear();
		up_keys_.clear();

		sf::Event event;
		while (window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_->close();

			events_.push_back(event);
		}
	}

	static bool GetKeyDown(const sf::Keyboard::Scancode key)
	{
		for (const sf::Event::KeyEvent key_event : instance_->down_keys_)
		{
			if (key_event.scancode == key)
			{
				return true;
			}
		}

		return false;
	}

	static bool GetKeyUp(const sf::Keyboard::Scancode key)
	{
		for (const sf::Event::KeyEvent key_event : instance_->up_keys_)
		{
			if (key_event.scancode == key)
			{
				return true;
			}
		}

		return false;
	}

	static bool GetKey(const sf::Keyboard::Scancode key)
	{
		for (const sf::Event::KeyEvent key_event : instance_->pressed_keys_)
		{
			if (key_event.scancode == key)
			{
				return true;
			}
		}

		return false;
	}
};

