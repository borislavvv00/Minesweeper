#pragma once
#include "../Field/Field.h"
#include "../Cell/Cell.h"
#include "../InputBar/InputBar.h"
#include <math.h>

class Game
{
private:
	std::vector<Cell*> cell;
	std::vector<Cell*> cell1;
	float x, y;
	int numberOfCells, numberOfMines, sqrtNumberOfCells;
	bool isMineExploded, isGamePaused;

	void CreateCells();
	void SetCells(std::vector<Cell*> &cell);

	void IncreaseCount(bool isMine, int &countSurroundedMines);
	void CheckCentralPart(int i, int &countSurroundedMines);
	void CheckFirstRow(int i, int &countSurroundedMines);
	void CheckLastRow(int i, int &countSurroundedMines);
	void CheckFirstColumn(int i, int &countSurroundedMines);
	void CheckLastColumn(int i, int &countSurroundedMines);
	void CheckCorners(int i, int &countSurroundedMines);
	void SetNumbers();

	void SetMines();

	void ReSetCells();
	void SetGameWindowParameters(int n);
	void StartGameWindow(sf::Window &window, sf::Text start, InputBar cellGrid, InputBar minesNumber);
public:
	Game()
	{
		isMineExploded = false;
		isGamePaused = false;
	}
	void CreateGameWindow();
	void CreateSettingsWindow();
};