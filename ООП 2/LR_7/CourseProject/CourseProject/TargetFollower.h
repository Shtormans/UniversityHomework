#pragma once
#include "MonoBehaviour.h"

#include <cmath>

#include "Time.h"
#define Speed 120

class TargetFollower : public MonoBehaviour
{
private:
	Transform* target_;

	void awake() override
	{
		target_ = nullptr;
	}

public:
	Transform* getTarget() const
	{
		return target_;
	}

	void setTarget(Transform* target)
	{
		target_ = target;
	}

	void moveToTarget()
	{
		sf::Vector2f movePosition = MoveTowards(transform->get_position(), target_->get_position(), Speed * 1 / 60);
		transform->set_position(movePosition);
	}

	sf::Vector2f MoveTowards(const sf::Vector2f& current, const sf::Vector2f& target, float maxDistanceDelta) {
		sf::Vector2f delta = target - current;
		float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

		if (distance <= maxDistanceDelta || distance == 0.f)
			return target;

		float scale = maxDistanceDelta / distance;
		return current + delta * scale;
	}
};

