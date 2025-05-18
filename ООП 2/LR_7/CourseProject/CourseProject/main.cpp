#include <iostream>
#include <SFML/Graphics.hpp>

#include "FiguresCreator.h"
#include "MonoBehaviour.h"
#include "GameObjectsContainer.h"
#include "Input.h"
#include "RuntimeProcessor.h"
#include "Screen.h"
#include "Time.h"

GameObject* add_objects(GameObjectsContainer* container)
{
	GameObject* mainObject = new GameObject();
	mainObject->add_component(new FiguresCreator());
	mainObject->add_component(new RuntimeProcessor());

	container->instantiate(mainObject);

	return mainObject;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default);

	sf::Clock clock;

	Input input(&window);
	Screen screen(&window);
	Time time(clock);

	GameObjectsContainer container;
	GameObject object(&container);

	GameObject* mainObject = add_objects(&container);

	RuntimeProcessor* processor = mainObject->get_component<RuntimeProcessor>();
	processor->prepare_threads();

	while (window.isOpen())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 120));
		std::lock_guard<std::mutex> lock(processor->mtx);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		screen.clear();
		time.restart();

		container.update(&window);

		screen.display();
	}

	processor->start_threads();

	return 0;
}
