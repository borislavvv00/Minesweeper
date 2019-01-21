#pragma once
#include <SFML/Graphics.hpp>

class Object
{
protected:
	sf::RectangleShape shape;
	sf::Texture texture;
public:
	virtual sf::RectangleShape& GetRectangleShape() = 0;
};