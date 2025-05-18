#include <iostream>
#include <SFML/Graphics.hpp>

#include "FiguresCreator.h"
#include "MonoBehaviour.h"
#include "GameObjectsContainer.h"
#include "Input.h"
#include "Screen.h"
#include "Time.h"

void add_objects(GameObjectsContainer* container)
{
	GameObject* mainObject = new GameObject();
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
	ShapeFactory shape_factory;

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
