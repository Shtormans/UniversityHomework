#include <iostream>
#include <SFML/Graphics.hpp>

#include "ColorChangeable.h"
#include "MonoBehaviour.h"
#include "GameObjectsContainer.h"
#include "Input.h"
#include "MouseFollower.h"
#include "MovableObject.h"
#include "Screen.h"
#include "SelectableObject.h"
#include "SelectablesContainer.h"
#include "Time.h"
#include "TrailCreator.h"
#include "VisibilitySetter.h"

void add_objects(GameObjectsContainer* container)
{
	GameObject* obj1 = new GameObject();

	obj1->add_component(new SelectableObject());
	obj1->add_component(new MovableObject());
	obj1->add_component(new Graphic());
	obj1->add_component(new ColorChangeable());
	obj1->add_component(new VisibilitySetter());
	obj1->add_component(new MouseFollower());

	container->Instantiate(obj1);

	GameObject* obj2 = new GameObject();

	obj2->add_component(new SelectableObject());
	obj2->add_component(new MovableObject());
	obj2->add_component(new Graphic());
	obj2->add_component(new ColorChangeable());
	obj2->add_component(new VisibilitySetter());
	obj2->add_component(new MouseFollower());

	container->Instantiate(obj2);
	obj2->transform->set_parent(obj1->transform);
	obj2->transform->set_position({ 100, 20 });

	GameObject* mainObject = new GameObject();
	mainObject->add_component(new SelectablesContainer());
	mainObject->add_component(new TrailCreator());

	container->Instantiate(mainObject);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	sf::Clock clock;

	Input input(&window);
	Screen screen(&window);
	Time time(clock);

	GameObjectsContainer container;
	GameObject object(&container);

	add_objects(&container);

	while (window.isOpen())
	{
		screen.clear();
		time.restart();

		container.update(&window);

		screen.display();
	}

	return 0;
}
