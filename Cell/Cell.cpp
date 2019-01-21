#include "Cell.h"

void Cell::SetTexture(std::string path)
{
	texture.loadFromFile(path);
}

void Cell::SetPosition(int x, int y)
{
	shape.setPosition(x, y);
}

void Cell::SetIndex(int n)
{
	index = n;
}

sf::RectangleShape& Cell::GetRectangleShape()
{
	return shape;
}

int Cell::GetIndex()
{
	return index;
}

void Cell::SetIsAbleToOpen(bool i)
{
	isAbleToOpen = i;
}

bool Cell::IsEmpty()
{
	return isEmpty;
}

bool Cell::IsAbleToOpen()
{
	return isAbleToOpen;
}

bool Cell::IsMine()
{
	return isMine;
}