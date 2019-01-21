#include "Game.h"
#include "../Player/Player.h"
#include "../GameStats/GameStats.h"
#include <SFML/Graphics.hpp>

void Game::ReSetCells()
{
	cell.clear();
	cell1.clear();

	CreateCells();
	SetCells(cell);
	SetCells(cell1);
	SetMines();
	SetNumbers();
}

void Game::StartGameWindow(sf::Window &window, sf::Text start, InputBar cellGrid)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (mousePosition.x >= start.getPosition().x && mousePosition.x <= 210)
	{
		if (mousePosition.y >= start.getPosition().y && mousePosition.y <= 166)
		{
			start.setFillColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				SetGameWindowParameters(cellGrid.GetInput());
				CreateGameWindow();
			}
		}
		else
		{
			start.setFillColor(sf::Color::White);
		}
	}
}

void Game::SetGameWindowParameters(int n)
{
	if (n < 100)
	{
		sqrtNumberOfCells = 10;
		numberOfCells = 100;
	}
	else if (n > 400)
	{
		sqrtNumberOfCells = 20;
		numberOfCells = 400;
	}
	else
	{
		sqrtNumberOfCells = round(sqrt(n));
		numberOfCells = pow(sqrtNumberOfCells, 2);
	}

	x = sqrtNumberOfCells * 31.f;
	y = sqrtNumberOfCells * 36.7f;

	if (numberOfMines >= numberOfCells)
	{
		numberOfMines  = numberOfCells - 1;
	}
	else if (numberOfMines <= 0)
	{
		numberOfMines = 1;
	}
}

void Game::CreateGameWindow()
{
	sf::RenderWindow window(sf::VideoMode(x, y), "Minesweeper");
	sf::Event event;
	Field field(x, y);
	Player player(sqrtNumberOfCells);
	GameStats gameStats(numberOfMines);

	sf::Font font;
	sf::Text win;
	font.loadFromFile("Fonts\\arial.ttf");
	win.setFont(font);
	win.setFillColor(sf::Color::Green);
	win.setString("You Win!");
	win.setCharacterSize(40);
	win.setPosition(x / 2 - 100, y / 2);

	sf::Text lose;
	font.loadFromFile("Fonts\\arial.ttf");
	lose.setFont(font);
	lose.setFillColor(sf::Color::Red);
	lose.setString("You Lose!");
	lose.setCharacterSize(40);
	lose.setPosition(x / 2 - 100, y / 2);

	CreateCells();
	SetCells(cell);
	SetCells(cell1);
	SetMines();
	SetNumbers();
	gameStats.SetPosition(x, y);
	ReSetCells();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (isGamePaused == false)
		{
			player.LeftClickOnCell(window, cell, cell1, isMineExploded);
			player.RightClickOnCell(window, cell, cell1);
		}

		if (gameStats.IsClickedOnStart(window, isMineExploded) == true)
		{
			ReSetCells();
		}

		gameStats.CountFlags(cell);

		window.clear();
		window.draw(field.GetRectangleShape());

		for (std::vector<Cell*>::iterator i = cell1.begin(); i != cell1.end(); i++)
		{
			window.draw((*i)->GetRectangleShape());
		}

		for (std::vector<Cell*>::iterator i = cell.begin(); i != cell.end(); i++)
		{
			window.draw((*i)->GetRectangleShape());
		}

		window.draw(gameStats.GetStartButtonShape());
		window.draw(gameStats.GetMinesCounterShape());
		window.draw(gameStats.GetTimerShape());
		window.draw(gameStats.GetMinesCounterText());
		window.draw(gameStats.GetTimerText());
		if (cell.size() == numberOfMines && isMineExploded == false)
		{
			window.draw(win);
			isGamePaused = true;
		}
		if (isMineExploded == true)
		{
			window.draw(lose);
			isGamePaused = true;
		}
		window.display();
	}
}

void Game::CreateSettingsWindow()
{
	sf::RenderWindow window(sf::VideoMode(310.f, 367.f), "Settings");
	sf::Event event;
	InputBar cellGrid(30, 160, 317.f, 10, "cell grid X*X = ");
	InputBar minesNumber(30, 120, 317.f, 180, "mines = ");

	sf::Font font;
	sf::Text start;
	font.loadFromFile("Fonts\\arial.ttf");
	start.setFont(font);
	start.setFillColor(sf::Color::White);
	start.setString("Start");
	start.setCharacterSize(60);
	start.setPosition(85.f, 103.f);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::TextEntered)
			{
				cellGrid.SetInputText(window, event);
				minesNumber.SetInputText(window, event);
			}
		}

		cellGrid.MouseOverInputBox(window);
		minesNumber.MouseOverInputBox(window);
		numberOfMines = minesNumber.GetInput();
		StartGameWindow(window, start, cellGrid);

		window.clear();
		window.draw(cellGrid.GetInputShape());
		window.draw(cellGrid.GetInputText());
		window.draw(minesNumber.GetInputShape());
		window.draw(minesNumber.GetInputText());
		window.draw(start);
		window.display();
	}
}