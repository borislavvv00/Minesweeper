#include "Game.h"
#include "../Cell/Cell.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>

void Game::IncreaseCount(bool isMine, int &countSurroundedMines)
{
	if (isMine == true)
	{
		countSurroundedMines++;
	}
}

void Game::CheckCentralPart(int i, int &countSurroundedMines)
{
	if (i > sqrtNumberOfCells && i < numberOfCells - sqrtNumberOfCells)
	{
		if (i % sqrtNumberOfCells > 0 && i % sqrtNumberOfCells < sqrtNumberOfCells - 1)
		{
			for (int h = -1; h <= 1; h++)
			{
				for (int v = -sqrtNumberOfCells; v <= sqrtNumberOfCells; v += sqrtNumberOfCells)
				{
					IncreaseCount(cell1[i + v + h]->isMine, countSurroundedMines);
				}
			}
		}
	}
}

void Game::CheckFirstRow(int i, int &countSurroundedMines)
{
	if (i > 0 && i < sqrtNumberOfCells - 1)
	{
		for (int h = -1; h <= 1; h++)
		{
			IncreaseCount(cell1[i + sqrtNumberOfCells + h]->isMine, countSurroundedMines);
			IncreaseCount(cell1[i + h]->isMine, countSurroundedMines);
		}
	}
}

void Game::CheckLastRow(int i, int &countSurroundedMines)
{
	if (i > numberOfCells - sqrtNumberOfCells && i < numberOfCells - 1)
	{
		for (int h = -1; h <= 1; h++)
		{
			IncreaseCount(cell1[i + h]->isMine, countSurroundedMines);
			IncreaseCount(cell1[i - sqrtNumberOfCells + h]->isMine, countSurroundedMines);
		}
	}
}

void Game::CheckFirstColumn(int i, int &countSurroundedMines)
{
	if (i % sqrtNumberOfCells == 0)
	{
		for (int v = -sqrtNumberOfCells; v <= sqrtNumberOfCells; v += sqrtNumberOfCells)
		{
			IncreaseCount(cell1[i + 1 + v]->isMine, countSurroundedMines);
			IncreaseCount(cell1[i + v]->isMine, countSurroundedMines);
		}
	}
}

void Game::CheckLastColumn(int i, int &countSurroundedMines)
{
	if (i % sqrtNumberOfCells == sqrtNumberOfCells - 1 && i > sqrtNumberOfCells - 1)
	{
		for (int v = -sqrtNumberOfCells; v <= sqrtNumberOfCells; v += sqrtNumberOfCells)
		{
			IncreaseCount(cell1[i - 1 + v]->isMine, countSurroundedMines);
			IncreaseCount(cell1[i + v]->isMine, countSurroundedMines);
		}
	}
}

void Game::CheckCorners(int i, int &countSurroundedMines)
{
	if (i == 0)
	{
		IncreaseCount(cell1[i + 1]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i + sqrtNumberOfCells]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i + sqrtNumberOfCells + 1]->isMine, countSurroundedMines);
	}

	if (i == sqrtNumberOfCells - 1)
	{
		IncreaseCount(cell1[i - 1]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i + sqrtNumberOfCells]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i + sqrtNumberOfCells - 1]->isMine, countSurroundedMines);
	}

	if (i == numberOfCells - sqrtNumberOfCells)
	{
		IncreaseCount(cell1[i + 1]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i - sqrtNumberOfCells]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i - sqrtNumberOfCells + 1]->isMine, countSurroundedMines);
	}

	if (i == numberOfCells - 1)
	{
		IncreaseCount(cell1[i - 1]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i - sqrtNumberOfCells]->isMine, countSurroundedMines);
		IncreaseCount(cell1[i - sqrtNumberOfCells - 1]->isMine, countSurroundedMines);
	}
}

void Game::SetNumbers()
{
	int countSurroundedMines = 0;
	for (int i = 0; i < numberOfCells; i++)
	{
		if (cell1[i]->isMine == false)
		{
			CheckCentralPart(i, countSurroundedMines);
			CheckFirstRow(i, countSurroundedMines);
			CheckLastRow(i, countSurroundedMines);

			if (i > 0 && i < numberOfCells - sqrtNumberOfCells)
			{
				CheckFirstColumn(i, countSurroundedMines);
				CheckLastColumn(i, countSurroundedMines);
			}

			CheckCorners(i, countSurroundedMines);
		}

		if (cell1[i]->isMine == false)
		{
			switch (countSurroundedMines)
			{
			case 0:
				cell1[i]->SetTexture("Images\\EmptyCell.png");
				cell1[i]->isEmpty = true;
				break;
			case 1:
				cell1[i]->SetTexture("Images\\One.png");
				break;
			case 2:
				cell1[i]->SetTexture("Images\\Two.png");
				break;
			case 3:
				cell1[i]->SetTexture("Images\\Three.png");
				break;
			case 4:
				cell1[i]->SetTexture("Images\\Four.png");
				break;
			case 5:
				cell1[i]->SetTexture("Images\\Five.png");
				break;
			case 6:
				cell1[i]->SetTexture("Images\\Six.png");
				break;
			case 7:
				cell1[i]->SetTexture("Images\\Seven.png");
				break;
			case 8:
				cell1[i]->SetTexture("Images\\Eighth.png");
				break;
			}
			countSurroundedMines = 0;
		}
	}
}

void Game::SetMines()
{
	int mineIndex;
	for (int i = 0; i < numberOfMines; i++)
	{
		mineIndex = rand() % numberOfCells;
		cell1[mineIndex]->SetTexture("Images\\Mine.png");
		cell1[mineIndex]->isMine = true;
	}
}

void Game::CreateCells()
{
	for (int i = 0; i < numberOfCells; i++)
	{
		cell.push_back(new Cell());
		cell[i]->SetIndex(i);
		cell1.push_back(new Cell());
		cell1[i]->SetIndex(i);
	}
}

void Game::SetCells(std::vector<Cell*> &cell)
{
	int r = 0;//rows
	int c = 0;//columns
	for (std::vector<Cell*>::iterator i = cell.begin(); i != cell.end(); i++)
	{
		(*i)->SetPosition(r * (*i)->size + sqrtNumberOfCells * 0.5f, c * (*i)->size + sqrtNumberOfCells * 5.7f);
		r++;
		if (r == sqrtNumberOfCells)
		{
			r = 0;
			c++;
		}
	}
}