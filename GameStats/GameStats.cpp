#include "GameStats.h"
#include "../Cell/Cell.h"
#include <SFML/Graphics.hpp>

sf::RectangleShape& GameStats::GetTimerShape()
{
	return timer;
}

sf::RectangleShape& GameStats::GetMinesCounterShape()
{
	return minesCounter;
}

sf::RectangleShape& GameStats::GetStartButtonShape()
{
	return startButton;
}

sf::Text& GameStats::GetMinesCounterText()
{
	return minesCounterText;
}

sf::Text& GameStats::GetTimerText()
{
	return timerText;
}

void GameStats::SetPosition(float x, float y)
{
	startButtonX = (x / 2) - 10.f;
	startButtonY = y / 17 - 6.f;
	startButton.setPosition(startButtonX, startButtonY);
	timer.setPosition((x / 3) - 90.f, y / 17 - 6.f);
	timerText.setPosition((x / 3) - 80.f, y / 17 - 6.f);
	minesCounter.setPosition((x / 3) + (x / 3) + 30.f, y / 17 - 6.f);
	minesCounterText.setPosition((x / 3) + (x / 3) + 50.f, y / 17 - 6.f);
}

void GameStats::CountFlags(std::vector<Cell*> &cell)
{
	int numberOfFlags = 0;
	for (std::vector<Cell*>::iterator it = cell.begin(); it != cell.end(); it++)
	{
		if ((*it)->IsAbleToOpen() == false)
		{
			numberOfFlags++;
		}
	}
	minesCounterText.setString(std::to_string(startingNumberOfMines - numberOfFlags));
	UpdateTimer();
}

void GameStats::UpdateTimer()
{
	seconds += 0.01f;
	if (seconds >= 60)
	{
		minutes++;
		seconds = 0;
	}
	int s = (int)seconds;
	timerText.setString(std::to_string(minutes) + ":" + std::to_string(s));
}

bool GameStats::IsClickedOnStart(sf::Window &window, bool &isMineExploded)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mousePosition.x >= startButtonX && mousePosition.x <= startButtonX + size)
		{
			if (mousePosition.y >= startButtonY && mousePosition.y <= startButtonY + size)
			{
				isMineExploded = false;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}