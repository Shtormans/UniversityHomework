#pragma once

#include "MonoBehaviour.h"
#include "Transform.h"

class GameObjectsContainer;

class GameObject
{
public:
	static GameObjectsContainer* objectsContainer_;

	int id;
	bool awakened_ = false;
	std::vector<MonoBehaviour*> components_;
	Transform* transform;


	GameObject(GameObjectsContainer* objectsContainer)
	{
		objectsContainer_ = objectsContainer;

		transform = new Transform(this);
	}

	GameObject()
	{
		transform = new Transform(this);
	}

	virtual ~GameObject()
	{
		delete transform;

		for (const auto component : components_)
		{
			delete component;
		}
	}

	void add_component(MonoBehaviour* component)
	{
		components_.push_back(component);

		component->AddData(this, transform);

		if (awakened_)
		{
			component->awake();
		}
	}

	void remove_component(MonoBehaviour* component)
	{
		components_.erase(std::remove(components_.begin(), components_.end(), component), components_.end());

		delete component;
	}

	template <typename T>
	T* get_component()
	{
		for (auto* component : components_)
		{
			if (T* instance = dynamic_cast<T*>(component))
			{
				return instance;
			}
		}

		return nullptr;
	}

	void awake()
	{
		awakened_ = true;

		for (const auto component : components_)
		{
			component->awake();
		}
	}

	void update() const
	{
		for (const auto component : components_)
		{
			component->update();
		}
	}

	void on_destroy() const
	{
		for (const auto component : components_)
		{
			component->on_destroy();
		}
	}

	virtual void on_collision_stay(GameObject* other)
	{
		for (const auto component : components_)
		{
			component->on_collision_stay(other);
		}
	}
};

