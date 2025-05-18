#pragma once
#include <map>

#include "FigureData.h"
#include "Input.h"
#include "Memento.h"
#include "MonoBehaviour.h"
#include "SelectablesContainer.h"

class PrototypeContainer : public MonoBehaviour
{
	std::map<int, FigureData> prototypes_;

	bool canAdd = true;
	bool canCreate = true;

	SelectablesContainer* container;
	FiguresCreator* creator;

	void awake() override
	{
		container = gameObject->get_component<SelectablesContainer>();
		creator = gameObject->get_component<FiguresCreator>();
	}

	void update() override
	{
		if (Input::get_key(sf::Keyboard::F1))
		{
			if (canAdd)
			{
				add_prototype();
			}

			canAdd = false;

		}
		else
		{
			canAdd = true;
		}

		if (Input::get_key(sf::Keyboard::F2))
		{
			if (canCreate)
			{
				create_prototype();
			}

			canCreate = false;

		}
		else
		{
			canCreate = true;
		}
	}

	void add_prototype()
	{
		int id;
		std::cout << "Set prototype id: ";
		std::cin >> id;

		SelectableObject* selected = container->last_selected;
		FigureData data = selected->gameObject->get_component<Memento>()->save();

		prototypes_[id] = data;
	}

	void create_prototype()
	{
		int id;
		std::cout << "select prototype from";
		for (auto pair: prototypes_)
		{
			std::cout << " " << pair.first;
		}
		std::cout << ": ";
		std::cin >> id;

		FigureData data = prototypes_[id];
		create_prototype(data, nullptr);
	}

	void create_prototype(FigureData& data, Transform* parent)
	{
		GameObject* figure = creator->create_object();
		figure->transform->set_parent(parent);

		figure->get_component<Memento>()->load(data, true);

		for (FigureData child : data.Children)
		{
			create_prototype(child, figure->transform);
		}
	}
};

