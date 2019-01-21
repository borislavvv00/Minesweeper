#include "InputBar.h"

sf::Text& InputBar::GetInputText()
{
	return inputText;
}

sf::RectangleShape& InputBar::GetInputShape()
{
	return inputShape;
}

bool InputBar::IsAddedNumberInteger()
{
	int numberOfCharecters = 0;
	for (int i = 0; i < addedNumber.getSize(); i++)
	{
		if ((int)addedNumber[i] <= 48 || (int)addedNumber[i] >= 57)
		{
			numberOfCharecters++;
		}
	}

	if (numberOfCharecters > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int InputBar::GetInput()
{
	if (addedNumber.getSize() == 0 || IsAddedNumberInteger() == false)
	{
		std::string s = "1";
		return std::stoi(s);
	}
	else
	{
		std::string s = addedNumber;
		return std::stoi(s);
	}
}

void InputBar::MouseOverInputBox(sf::Window &window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (mousePosition.x >= inputShape.getPosition().x && mousePosition.x <= inputShape.getPosition().x + xSize)
	{
		if (mousePosition.y >= inputShape.getPosition().y && mousePosition.y <= inputShape.getPosition().y + ySize)
		{
			inputText.setFillColor(sf::Color::Blue);
		}
	}
	else
	{
		inputText.setFillColor(sf::Color::Black);
	}
}

void InputBar::SetInputText(sf::Window &window, sf::Event &event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

	if (mousePosition.x >= inputShape.getPosition().x && mousePosition.x <= inputShape.getPosition().x + xSize)
	{
		if (mousePosition.y >= inputShape.getPosition().y && mousePosition.y <= inputShape.getPosition().y + ySize)
		{
			input += event.text.unicode;
			addedNumber += event.text.unicode;

			if (addedNumber.getSize() > 3)
			{
				input = startingInput + event.text.unicode;
				addedNumber = "";
			}

			inputText.setString(input);
		}
	}
}