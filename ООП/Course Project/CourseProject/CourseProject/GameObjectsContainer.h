#pragma once
#include <vector>

class GameObjectsContainer
{
private:
	std::vector<GameObject*> objects_;

public:
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

	void update(sf::RenderWindow* window) const
	{
		for (auto object : objects_)
		{
			object->update(window);
		}
	}
};

