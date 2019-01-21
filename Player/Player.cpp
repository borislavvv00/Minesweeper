#include "Player.h"
#include "../Cell/Cell.h"
#include <SFML/Graphics.hpp>

void Player::ClickOnNonEmptyCell(std::vector<Cell*> &cell, std::vector<Cell*> cell1, std::vector<Cell*>::iterator &i, bool &isMineExploded)
{
	for (std::vector<Cell*>::iterator it = cell1.begin(); it != cell1.end(); it++)
	{
		if ((*it)->GetIndex() == (*i)->GetIndex())
		{
			if ((*it)->IsEmpty() == false)
			{
				if ((*it)->IsMine() == true)
				{
					(*it)->SetTexture("Images\\ExplodedMine.png");
					isMineExploded = true;
				}
				DeleteCell(cell, i);
				break;
			}
		}
	}
}

void Player::LeftClickOnCell(sf::Window &window, std::vector<Cell*> &cell, std::vector<Cell*> &cell1, bool &isMineExploded)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (std::vector<Cell*>::iterator i = cell.begin(); i != cell.end(); i++)
		{
			if (mousePosition.x >= (*i)->GetRectangleShape().getPosition().x && mousePosition.x <= (*i)->GetRectangleShape().getSize().x + (*i)->GetRectangleShape().getPosition().x)
			{
				if (mousePosition.y >= (*i)->GetRectangleShape().getPosition().y && mousePosition.y <= (*i)->GetRectangleShape().getSize().y + (*i)->GetRectangleShape().getPosition().y)
				{
					if ((*i)->GetRectangleShape().getTexture() != &textureFlag)
					{
						ClickOnNonEmptyCell(cell, cell1, i, isMineExploded);
						ClickOnEmptyCell((*i)->GetIndex(), cell, cell1);

						//Check if deleted cells are empty
						for (int j = 0; j < deletedCells.size(); j++)
						{
							ClickOnEmptyCell(deletedCells[j], cell, cell1);
						}
						deletedCells.clear();
						break;
					}
				}
			}
		}
	}
}

void Player::RightClickOnCell(sf::Window &window, std::vector<Cell*> &cell, std::vector<Cell*> &cell1)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		for (std::vector<Cell*>::iterator i = cell.begin(); i != cell.end(); i++)
		{
			if (mousePosition.x >= (*i)->GetRectangleShape().getPosition().x && mousePosition.x <= (*i)->GetRectangleShape().getSize().x + (*i)->GetRectangleShape().getPosition().x)
			{
				if (mousePosition.y >= (*i)->GetRectangleShape().getPosition().y && mousePosition.y <= (*i)->GetRectangleShape().getSize().y + (*i)->GetRectangleShape().getPosition().y)
				{
					if (isFlagPlaced == false)
					{
						(*i)->GetRectangleShape().setTexture(&textureFlag);
						(*i)->SetIsAbleToOpen(false);
						isFlagPlaced = true;
					}
					else
					{
						(*i)->GetRectangleShape().setTexture(&textureUnCheckedCell);
						(*i)->SetIsAbleToOpen(true);
						isFlagPlaced = false;
					}
				}
			}
		}
	}
}