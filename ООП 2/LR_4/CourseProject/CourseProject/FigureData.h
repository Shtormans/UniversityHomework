#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "Graphic.h"

struct FigureData
{
	int Id;
	sf::Vector2f Position;
	sf::Color Color;
	GraphicForm Form;
	std::vector<FigureData> Children;
};

