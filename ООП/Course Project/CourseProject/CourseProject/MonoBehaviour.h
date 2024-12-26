#pragma once

#include "Transform.h"

class MonoBehaviour
{
public:
	GameObject* gameObject;
	Transform* transform;

	virtual ~MonoBehaviour() = default;

	void AddData(GameObject* gameObject, Transform* transform)
	{
		this->gameObject = gameObject;
		this->transform = transform;
	}

	virtual void update() {}
	virtual void awake() {}
	virtual void on_destroy() {}
	virtual void on_collision_stay(GameObject* other) {}
};

