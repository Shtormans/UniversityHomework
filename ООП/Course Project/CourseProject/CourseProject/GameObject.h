#pragma once
#include <vector>

class GameObject
{
private:
	GameObject* parent_ = nullptr;
	std::vector<GameObject*> children_;

public:
	GameObject(std::vector<GameObject*> children, GameObject* parent = nullptr)
		: parent_(parent), children_(std::move(children))
	{
		
	}

	virtual void update()
	{
		for (const auto child: children_)
		{
			child->update();
		}
	}

	virtual void awake()
	{
		for (const auto child : children_)
		{
			child->awake();
		}
	}
};

