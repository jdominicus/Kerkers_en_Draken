#include "UserInterface.h"
#include "StringClass.h"

#include <iostream> 

UserInterface::UserInterface()
{
}

UserInterface::~UserInterface()
{
}

int UserInterface::getInputInt(const char* message, int min, int max) const
{
	std::cout << message;
	int input;

	while (true)
	{
		if (std::cin >> input && input >= min && input <= max)
			return input;
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Enter a valid number (" << min << "-" << max << "): ";
		}
	}
}

StringClass UserInterface::getInputString(const char* message, int min, int max) const
{
	std::cout << message;
	StringClass input("");

	while (true)
	{
		char* inputChar = new char[max + 1];
		inputChar[max] = '\0';
		std::cin.get(inputChar, max, '\n');
		
		input.append(inputChar);
		delete[] inputChar;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		if (input.getLength() >= min && input.getLength() <= max)
			return input;
		else
			std::cout << "Enter a valid input (" << min << "-" << max << " characters): ";
	}
}
