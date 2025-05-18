#pragma once

#include <fstream>

#include "FigureData.h"
#include "Memento.h"

class SceneSaverLoader : public MonoBehaviour
{
	FiguresCreator* creator_;
	bool canSave_;

	const std::string File = "scene.txt";

	void awake() override
	{
		creator_ = gameObject->get_component<FiguresCreator>();
		canSave_ = true;

		load();
	}

	void update() override
	{
		if (Input::get_key(sf::Keyboard::L))
		{
			if (!canSave_)
			{
				return;
			}

			canSave_ = false;

			save();
		}
		else
		{
			canSave_ = true;
		}
	}

	void save()
	{
		std::ofstream stream(File);
		std::map<int, std::vector<int>> children;

		for (GameObject* toSave : GameObject::objectsContainer_->objects_)
		{
			if (toSave == gameObject)
			{
				continue;
			}

			save_object(toSave, stream);
			size_t childCount = toSave->transform->children_.size();

			if (childCount == 0)
			{
				continue;
			}

			std::vector<int> childrenIds;

			for (Transform* child : toSave->transform->children_)
			{
				childrenIds.push_back(child->gameObject->id);
			}

			children[toSave->id] = childrenIds;
		}


		stream << "|";

		for (auto parent : children)
		{
			stream << '\n' << parent.first;

			for (int childId : parent.second)
			{
				stream << ' ' << childId;
			}

			stream << " |";
		}

		stream.close();
	}

	void load()
	{
		std::ifstream stream(File);

		if (!stream.is_open())
		{
			return;
		}

		std::string word;
		std::vector<std::string> words;

		while (stream >> word)
		{
			words.push_back(word);
		}

		stream.close();

		int endWordIndex = 0;
		std::vector<GameObject*> objects;

		for (int i = 0; i < words.size();)
		{
			if (words[i] == "|")
			{
				endWordIndex = i;
				break;
			}

			int id = stoi(words[i]);

			sf::Vector2f position;
			position.x = stof(words[i + 1]);
			position.y = stof(words[i + 2]);

			sf::Color color;
			color.r = stoi(words[i + 3]);
			color.g = stoi(words[i + 4]);
			color.b = stoi(words[i + 5]);
			color.a = stoi(words[i + 6]);

			GraphicForm form = (GraphicForm)stoi(words[i + 7]);

			GameObject* figure = creator_->create_object();

			FigureData data =
			{
				id,
				position,
				color,
				form
			};

			figure->get_component<Memento>()->load(data);
			objects.push_back(figure);

			i += 8;
		}

		for (int i = endWordIndex + 1; i < words.size();)
		{
			int parentId = stoi(words[i]);
			GameObject* parent = get_by_id(objects, parentId);

			int j = i + 1;
			while (words[j] != "|")
			{
				int childId = stoi(words[j]);
				GameObject* child = get_by_id(objects, childId);

				child->transform->set_parent(parent->transform);

				j++;
			}

			i = j + 1;
		}
	}

	void save_object(GameObject* toSave, std::ofstream& stream)
	{
		FigureData data = toSave->get_component<Memento>()->save();
		stream << data.Id << ' ' << data.Position.x << ' ' << data.Position.y << ' ' << (int)data.Color.r << ' ' << (int)data.Color.g << ' ' << (int)data.Color.b << ' ' << (int)data.Color.a << ' ' << data.Form << '\n';
	}

	GameObject* get_by_id(std::vector<GameObject*> objects, int id)
	{
		for (GameObject* object : objects)
		{
			if (object->id == id)
			{
				return object;
			}
		}

		return nullptr;
	}
};

