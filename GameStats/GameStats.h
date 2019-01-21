#pragma once
#include "../Game/Game.h"

class GameStats
{
private:
	sf::RectangleShape timer, minesCounter, startButton;
	sf::Texture textureStartButton;
	sf::Text minesCounterText, timerText;
	sf::Font font;
	const int startingNumberOfMines;
	int  minutes, minesLeft, size;
	float startButtonX, startButtonY, seconds;
	void UpdateTimer();
public:
	GameStats(int numberOfMines) : minesLeft(numberOfMines), startingNumberOfMines(numberOfMines)
	{
		minutes = 0;
		seconds = 0;
		size = 30;
		startButtonX = 0;
		startButtonY = 0;

		textureStartButton.loadFromFile("Images\\StartButton.png");
		startButton.setSize(sf::Vector2f(size, size));
		startButton.setTexture(&textureStartButton);

		minesCounter.setSize(sf::Vector2f(size * 2, size));
		minesCounter.setFillColor(sf::Color::Black);

		timer.setSize(sf::Vector2f(size * 2, size));
		timer.setFillColor(sf::Color::Black);

		font.loadFromFile("Fonts\\arial.ttf");
		minesCounterText.setFont(font);
		minesCounterText.setString(std::to_string(minesLeft));
		minesCounterText.setCharacterSize(20);
		minesCounterText.setFillColor(sf::Color::Red);

		timerText.setFont(font);
		timerText.setString(std::to_string(minutes) + ":" + std::to_string(seconds));
		timerText.setCharacterSize(20);
		timerText.setFillColor(sf::Color::Red);
	}
	sf::RectangleShape& GetTimerShape();
	sf::RectangleShape& GetMinesCounterShape();
	sf::RectangleShape& GetStartButtonShape();
	sf::Text& GetMinesCounterText();
	sf::Text& GetTimerText();
	void SetPosition(float x, float y);
	void CountFlags(std::vector<Cell*> &cell);
	bool IsClickedOnStart(sf::Window &window, bool &isMineExploded);
};