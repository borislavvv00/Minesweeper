#pragma once
#include "../Object.h"

class Cell : protected Object
{
private:
	int size, index;
	bool isMine, isNumber, isEmpty, isAbleToOpen;

	void SetIndex(int n);
	void SetPosition(int x, int y);
public:
	Cell()
	{
		size = 30;
		index = 0;
		texture.loadFromFile("Images\\UnCheckedCell.png");
		shape.setSize(sf::Vector2f(size, size));
		shape.setTexture(&texture);
		isMine = false;
		isNumber = false;
		isEmpty = false;
		isAbleToOpen = true;
	}
	sf::RectangleShape& GetRectangleShape();
	int GetIndex();

	void SetIsAbleToOpen(bool i);
	void SetTexture(std::string path);

	bool IsEmpty();
	bool IsAbleToOpen();
	bool IsMine();
	friend class Game;
};