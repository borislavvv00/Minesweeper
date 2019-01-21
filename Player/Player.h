#pragma once
#include "../Game/Game.h"
#include "../GameStats/GameStats.h"

class Player
{
private:
	sf::Texture textureFlag, textureUnCheckedCell, textureMineBlow;
	int sqrtNumberOfCells;
	std::vector<int> deletedCells;
	bool isFlagPlaced;

	void DeleteCell(std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j);
	void DeleteHorizontally(int index, int m, int k, std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j);
	void DeleteVertically(int l, int n, int m, std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j);
	void DeleteDiagonally(int index, int l, int n, int k, int m, std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j);
public:
	Player(int n) : sqrtNumberOfCells(n)
	{
		textureFlag.loadFromFile("Images\\Flag.png");
		textureUnCheckedCell.loadFromFile("Images\\UnCheckedCell.png");
		textureMineBlow.loadFromFile("Images\\ExplodedMine.png");
		isFlagPlaced = false;
	}

	void LeftClickOnCell(sf::Window &window, std::vector<Cell*> &cell, std::vector<Cell*> &cell1, bool &isMineExploded);
	void RightClickOnCell(sf::Window &window, std::vector<Cell*> &cell, std::vector<Cell*> &cell1);
	void ClickOnEmptyCell(int index, std::vector<Cell*> &cell, std::vector<Cell*> cell1);
	void ClickOnNonEmptyCell(std::vector<Cell*> &cell, std::vector<Cell*> cell1, std::vector<Cell*>::iterator &i, bool &isMineExploded);
};