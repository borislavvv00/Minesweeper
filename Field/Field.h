#pragma once
#include "../Object.h"

class Field : protected Object
{
public:
	Field(float x, float y)
	{
		texture.loadFromFile("Images\\MinesweeperField.png");
		shape.setSize(sf::Vector2f(x, y));
		shape.setPosition(0, 0);
		shape.setTexture(&texture);
	}
	sf::RectangleShape& GetRectangleShape();
};