#pragma once
#include <vector>

#include "GameObject.h"

class GameObjectsContainer
{
public:
	std::vector<GameObject*> objects_;

	GameObjectsContainer() = default;

	void Instantiate(GameObject* object, Transform* parent = nullptr)
	{
		objects_.push_back(object);

		object->transform->set_parent(parent);
		object->awake();
	}

	void Destroy(GameObject* object)
	{
		objects_.erase(std::remove(objects_.begin(), objects_.end(), object), objects_.end());

		object->transform->set_parent(nullptr);
		object->on_destroy();

		delete object;
	}

	template<typename T>
	std::vector<T*> find_of_type()
	{
		std::vector<T*> foundObjects;

		for (auto* object : objects_) {
			if (T* component = object->get_component<T>()) {
				foundObjects.push_back(component);
			}
		}

		return foundObjects;
	}

	void update(sf::RenderWindow* window) const
	{
		for (auto object : objects_)
		{
			object->update();
		}
	}
};

