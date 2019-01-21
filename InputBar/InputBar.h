#pragma once
#include <SFML/Graphics.hpp>

class InputBar
{
private:
	const sf::String startingInput;
	sf::String input, addedNumber;
	sf::Text inputText;
	sf::Font font;
	sf::RectangleShape inputShape;
	int ySize, xSize, yCoord, xCoord;
	bool IsAddedNumberInteger();
public:
	InputBar(int yS, int xS, int yC, int xC, sf::String in) : ySize(yS), xSize(xS), yCoord(yC), xCoord(xC), input(in), startingInput(in)
	{
		font.loadFromFile("Fonts\\arial.ttf");

		inputShape.setFillColor(sf::Color::White);
		inputShape.setSize(sf::Vector2f(xSize, ySize));
		inputShape.setPosition(xCoord, yCoord);
		inputText.setPosition(xCoord, yCoord);
		inputText.setFillColor(sf::Color::Black);
		inputText.setCharacterSize(20);
		inputText.setString(input);
		inputText.setFont(font);
	}
	sf::Text& GetInputText();
	sf::RectangleShape& GetInputShape();
	int GetInput();
	void MouseOverInputBox(sf::Window &window);
	void SetInputText(sf::Window &window, sf::Event &event);
};