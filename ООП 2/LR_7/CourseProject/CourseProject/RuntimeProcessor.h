#pragma once

#include <mutex>
#include <thread>
#include "FiguresCreator.h"
#include "MonoBehaviour.h"
#include "Screen.h"
#include "TargetFollower.h"

#define SpawnInterval 400
#define MaxFigures 10

class RuntimeProcessor : public MonoBehaviour
{
	FiguresCreator* creator_;
	GameObject* createdFigures_[MaxFigures];

	void awake() override
	{
		for (int i = 0; i < MaxFigures; i++)
		{
			createdFigures_[i] = nullptr;
		}

		creator_ = gameObject->get_component<FiguresCreator>();
	}

	int getFiguresCount(GameObject** figures)
	{
		int amount = 0;

		for (int i = 0; i < MaxFigures; i++)
		{
			if (figures[i] != nullptr)
			{
				amount++;
			}
		}

		return amount;
	}

	void getArrayCopy(GameObject* destination[MaxFigures]) {
		for (int i = 0; i < MaxFigures; ++i) {
			destination[i] = createdFigures_[i];
		}
	}

	void updateFigures(GameObject* updateArray[MaxFigures])
	{
		for (int i = 0; i < MaxFigures; ++i) {
			createdFigures_[i] = updateArray[i];
		}
	}

	void addFigures()
	{
		while (Screen::get_window()->isOpen())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(SpawnInterval));
			std::lock_guard<std::mutex> lock(mtx);

			GameObject* figuresCopy[MaxFigures];
			getArrayCopy(figuresCopy);

			int figuresCount = getFiguresCount(figuresCopy);

			if (figuresCount >= MaxFigures)
			{
				continue;
			}

			GameObject* figure = creator_->create_object();

			sf::Vector2f screenSize = Screen::get_size();
			float x = Utils::randInclusive(0, screenSize.x);
			float y = Utils::randInclusive(0, screenSize.y);

			figure->transform->set_position(sf::Vector2f(x, y));

			for (int i = 0; i < MaxFigures; i++)
			{
				if (figuresCopy[i] == nullptr)
				{
					figuresCopy[i] = figure;
					break;
				}
			}

			updateFigures(figuresCopy);
		}
	}

	void assignTargets()
	{
		while (Screen::get_window()->isOpen())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
			std::lock_guard<std::mutex> lock(mtx);

			GameObject* figuresCopy[MaxFigures];
			getArrayCopy(figuresCopy);

			for (auto figure : figuresCopy)
			{
				if (figure == nullptr)
				{
					continue;
				}

				TargetFollower* follower = figure->get_component<TargetFollower>();

				if (follower == nullptr)
				{
					continue;
				}

				if (follower->getTarget() == nullptr)
				{
					int targetIndex = Utils::randInclusive(0, MaxFigures - 1);
					GameObject* target = figuresCopy[targetIndex];

					int attempts = MaxFigures;
					while (attempts > 0 && (target == nullptr || target == figure))
					{
						targetIndex = (targetIndex + 1) % MaxFigures;
						target = figuresCopy[targetIndex];

						attempts--;
					}

					if (target == nullptr || target == figure)
					{
						continue;
					}

					follower->setTarget(target->transform);
				}
			}
		}
	}

	void moveFigures()
	{
		while (Screen::get_window()->isOpen())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
			std::lock_guard<std::mutex> lock(mtx);

			GameObject* figuresCopy[MaxFigures];
			getArrayCopy(figuresCopy);

			for (GameObject* figure : figuresCopy)
			{
				if (figure == nullptr)
				{
					continue;
				}

				TargetFollower* follower = figure->get_component<TargetFollower>();

				if (follower->getTarget() != nullptr)
				{
					follower->moveToTarget();
				}
			}
		}
	}

	void removeCollisions()
	{
		while (Screen::get_window()->isOpen())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
			std::lock_guard<std::mutex> lock(mtx);

			GameObject* figuresCopy[MaxFigures];
			getArrayCopy(figuresCopy);

			std::vector<int> toDelete;

			for (int i = 0; i < MaxFigures; i++)
			{
				GameObject* figure = figuresCopy[i];
				if (figure == nullptr)
				{
					continue;
				}

				std::vector<GameObject*> collisions = GameObject::objectsContainer_->check_for_collision(figure);

				if (collisions.size() == 0)
				{
					continue;
				}

				TargetFollower* follower = figure->get_component<TargetFollower>();
				if (follower->getTarget() == nullptr)
				{
					continue;
				}

				bool collided = false;
				for (auto other : collisions)
				{
					if (follower->getTarget()->gameObject == other)
					{
						collided = true;
						break;
					}
				}

				if (!collided)
				{
					continue;
				}

				toDelete.push_back(i);

				for (int j = 0; j < MaxFigures; j++)
				{
					if (figuresCopy[j] == follower->getTarget()->gameObject)
					{
						toDelete.push_back(j);
					}
				}
			}

			for (int to_delete : toDelete)
			{
				GameObject* figure = figuresCopy[to_delete];

				if (figure == nullptr)
				{
					continue;
				}

				for (GameObject* follower : figuresCopy)
				{
					if (follower == nullptr)
					{
						continue;
					}

					TargetFollower* component = follower->get_component<TargetFollower>();
					if (component->getTarget() != nullptr && component->getTarget()->gameObject == figure)
					{
						component->setTarget(nullptr);
					}
				}

				GameObject::objectsContainer_->destroy(figure);
				figuresCopy[to_delete] = nullptr;
			}

			updateFigures(figuresCopy);
		}
	}

	std::thread* addFiguresThread;
	std::thread* assignTargetsThread;
	std::thread* moveFiguresThread;
	std::thread* removeCollisionsThread;

public:
	std::mutex mtx;

	void prepare_threads()
	{
		addFiguresThread = new std::thread(&RuntimeProcessor::addFigures, this);
		assignTargetsThread = new std::thread(&RuntimeProcessor::assignTargets, this);
		moveFiguresThread = new std::thread(&RuntimeProcessor::moveFigures, this);
		removeCollisionsThread = new std::thread(&RuntimeProcessor::removeCollisions, this);
	}

	void start_threads()
	{
		addFiguresThread->join();
		assignTargetsThread->join();
		moveFiguresThread->join();
		removeCollisionsThread->join();
	}
};

