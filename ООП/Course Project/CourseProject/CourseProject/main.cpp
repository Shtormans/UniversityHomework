#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "GameObjectsContainer.h"
#include "Input.h"
#include "MovableObject.h"
#include "Screen.h"
#include "Time.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	sf::Clock clock;

	Input manager(&window);
	Screen screen(&window);
	Time time(clock);

	GameObjectsContainer container;
	container.Instantiate(new MovableObject());

	GameObject object(&container);

	while (window.isOpen())
	{
		window.clear();
		time.restart();

		container.update(&window);

		window.display();
	}

	return 0;
}
