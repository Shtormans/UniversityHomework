#pragma once
#include <vector>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

class GameObject;

class Transform : public sf::Transform
{
private:
	sf::Vector2f position_;

	Transform* parent_;
	std::vector<Transform*> children_;

	sf::Vector2f get_parent_position() const
	{
		if (parent_ == nullptr)
		{
			return sf::Vector2f(0, 0);
		}

		return parent_->get_position();
	}

public:
	GameObject* gameObject;


	Transform(GameObject* gameObject)
	{
		parent_ = nullptr;
		this->gameObject = gameObject;
	}

	sf::Vector2f get_position() const
	{
		return position_;
	}

	void set_position(sf::Vector2f position)
	{
		for (auto child : children_)
		{
			child->set_position(position + child->get_local_position());
		}

		sf::Vector2f delta = position - position_;
		translate(delta.x, delta.y);

		position_ = position;
	}

	sf::Vector2f get_local_position() const
	{
		return position_ - get_parent_position();
	}

	void set_local_position(sf::Vector2f position)
	{
		set_position(position + get_parent_position());
	}

	Transform* get_parent() const
	{
		return parent_;
	}

	void set_parent(Transform* parent)
	{
		if (parent_ != nullptr)
		{
			parent_->children_.erase(std::remove(parent_->children_.begin(), parent_->children_.end(), this), parent_->children_.end());
		}

		parent_ = parent;

		if (parent_ != nullptr)
		{
			parent_->children_.push_back(this);
		}
	}
};

