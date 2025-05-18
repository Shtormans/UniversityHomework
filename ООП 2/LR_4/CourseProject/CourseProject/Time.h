#pragma once
#include <SFML/System/Clock.hpp>

class Time
{
private:
	static Time* instance_;

	sf::Clock clock_;
	float elapsedTime_;

public:
	Time(sf::Clock clock)
	{
		if (instance_ != nullptr)
		{
			return;
		}

		instance_ = this;
		clock_ = clock;
	}

	void restart()
	{
		elapsedTime_ = clock_.restart().asSeconds();
	}

	static float get_delta_time()
	{
		return instance_->elapsedTime_;
	}
};

