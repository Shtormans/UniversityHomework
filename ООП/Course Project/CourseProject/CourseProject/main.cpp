#include <iostream>
#include <SFML/Graphics.hpp>

#include "ColorChangeable.h"
#include "CompositeCreator.h"
#include "FiguresCreator.h"
#include "MonoBehaviour.h"
#include "GameObjectsContainer.h"
#include "Input.h"
#include "MouseFollower.h"
#include "MovableObject.h"
#include "Retracter.h"
#include "Screen.h"
#include "SelectableObject.h"
#include "SelectablesContainer.h"
#include "Time.h"
#include "TrailCreator.h"
#include "VisibilitySetter.h"

void add_objects(GameObjectsContainer* container)
{
	GameObject* mainObject = new GameObject();
	mainObject->add_component(new SelectablesContainer());
	mainObject->add_component(new TrailCreator());
	mainObject->add_component(new CompositeCreator());
	mainObject->add_component(new FiguresCreator());

	container->instantiate(mainObject);
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
