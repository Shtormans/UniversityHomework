#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Transform.h"

class GameObjectsContainer;

class GameObject
{
protected:
	static GameObjectsContainer* objectsContainer_;

public:
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
	}

	virtual void update(sf::RenderWindow* window)
	{

	}

	virtual void awake()
	{
	}

	virtual void on_destroy()
	{
		
	}
};

