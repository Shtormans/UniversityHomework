#include <SFML/Graphics.hpp>

#include "EventManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    EventManager manager(&window);

    while (window.isOpen())
    {
        manager.UpdateEvents();

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
