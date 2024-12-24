#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Transform.h"

class GameObjectsContainer;

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

