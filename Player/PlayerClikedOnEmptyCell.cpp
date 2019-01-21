#pragma once
#include "Player.h"
#include "../Cell/Cell.h"

void Player::DeleteCell(std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j)
{
	if (j != cell.end() - 1)
	{
		j = cell.erase(j);
	}
	else //if it is the last cell
	{
		if (cell.size() != 1)
		{
			j = cell.erase(j);
			j--;
		}
		else //if it is a single cell
		{
			cell.clear();
		}
	}
}

void Player::DeleteHorizontally(int index, int m, int k, std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j)
{
	if (m == (*j)->GetIndex())
	{
		if (index % sqrtNumberOfCells != k)
		{
			if ((*j)->IsAbleToOpen() == true)
			{
				deletedCells.push_back((*j)->GetIndex());
				DeleteCell(cell, j);
			}
			else
			{
				return;
			}

			if (cell.size() > 0 && m < index)
			{
				j = cell.begin();
			}
		}
	}
}

void Player::DeleteVertically(int l, int n, int m, std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j)
{
	if (l > n && m == (*j)->GetIndex())
	{
		if ((*j)->IsAbleToOpen() == true)
		{
			deletedCells.push_back((*j)->GetIndex());
			DeleteCell(cell, j);
		}
		else
		{
			return;
		}
	}
}

void Player::DeleteDiagonally(int index, int l, int n, int k, int m, std::vector<Cell*> &cell, std::vector<Cell*>::iterator &j)
{
	if (l > n)
	{
		if (index % sqrtNumberOfCells != k)
		{
			if (m == (*j)->GetIndex())
			{
				if ((*j)->IsAbleToOpen() == true)
				{
					deletedCells.push_back((*j)->GetIndex());
					DeleteCell(cell, j);
				}
				else
				{
					return;
				}

				if (cell.size() > 0 && m < index + sqrtNumberOfCells)
				{
					j = cell.begin();
				}
			}
		}
	}
}

void Player::ClickOnEmptyCell(int index, std::vector<Cell*> &cell, std::vector<Cell*> cell1)
{
	for (std::vector<Cell*>::iterator it = cell1.begin(); it != cell1.end(); it++)
	{
		if ((*it)->IsEmpty() == true)
		{
			if ((*it)->GetIndex() == index)
			{
				for (std::vector<Cell*>::iterator j = cell.begin(); j != cell.end(); j++)
				{
					//center
					if (index == (*j)->GetIndex())
					{
						DeleteCell(cell, j);
					}
					//left
					if (index > 0)
					{
						DeleteHorizontally(index, (*(it - 1))->GetIndex(), 0, cell, j);
					}
					//right
					if ((*(cell.end() - 1))->GetIndex() > index)
					{
						DeleteHorizontally(index, (*(it + 1))->GetIndex(), sqrtNumberOfCells - 1, cell, j);
					}
					//up
					DeleteVertically(index, sqrtNumberOfCells - 1, (*it)->GetIndex() - sqrtNumberOfCells, cell, j);
					//down
					DeleteVertically((*(cell.end() - 1))->GetIndex() - sqrtNumberOfCells + 1, index, (*it)->GetIndex() + sqrtNumberOfCells, cell, j);
					//upLeft
					DeleteDiagonally(index, index, sqrtNumberOfCells, 0, (*it)->GetIndex() - sqrtNumberOfCells - 1, cell, j);
					//upRight
					DeleteDiagonally(index, index, sqrtNumberOfCells - 1, sqrtNumberOfCells - 1, (*it)->GetIndex() - sqrtNumberOfCells + 1, cell, j);
					//downLeft
					DeleteDiagonally(index, (*(cell.end() - 1))->GetIndex() - sqrtNumberOfCells + 1, index, 0, (*it)->GetIndex() + sqrtNumberOfCells - 1, cell, j);
					//downRight
					DeleteDiagonally(index, (*(cell.end() - 1))->GetIndex() - sqrtNumberOfCells, index, sqrtNumberOfCells - 1, (*it)->GetIndex() + sqrtNumberOfCells + 1, cell, j);
					
					if (cell.size() == 0)
					{
						break;
					}
				}
				break;
			}
		}
	}
}