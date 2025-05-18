#pragma once
#include <vector>

#include "GameObject.h"

class GameObjectsContainer
{
private:
	void check_for_collision() const
	{
		for (int i = 0; i < objects_.size(); i++)
		{
			auto object = objects_[i];
			Graphic* graphic = object->get_component<Graphic>();

			if (graphic == nullptr)
			{
				continue;
			}

			for (int j = i + 1; j < objects_.size(); j++)			
			{
				auto other = objects_[j];

				Graphic* otherGraphic = other->get_component<Graphic>();

				if (otherGraphic == nullptr)
				{
					continue;
				}

				if (graphic->collides(otherGraphic->get_rect()))
				{
					object->on_collision_stay(other);
					other->on_collision_stay(object);
				}
			}
		}
	}

public:
	std::vector<GameObject*> objects_;
	std::vector<GameObject*> to_add_;

	GameObjectsContainer() = default;

	void instantiate(GameObject* object, Transform* parent = nullptr)
	{
		to_add_.push_back(object);

		object->transform->set_parent(parent);
		object->awake();
	}

	void destroy(GameObject* object)
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

	void update(sf::RenderWindow* window)
	{
		for (auto object : objects_)
		{
			object->update();
		}

		check_for_collision();

		for (auto element : to_add_)
		{
			objects_.push_back(element);
		}

		to_add_.clear();
	}
};

