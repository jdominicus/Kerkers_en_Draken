#include "Application.h"
#include "Dungeon.h"
#include "Player.h"
#include "StringClass.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Application::Application() : gameState{ 0 }, running{ true }
{
}

Application::~Application()
{
	if (dungeon != nullptr)
		delete dungeon;

	if (player != nullptr)
		delete player;

	RandomNumberGenerator::removeRandom();
}

void Application::start()
{
	while (running)
	{
		displayOptions();
		int input = handleUserInput();
		handleOptions(input);
	}
}

void Application::createNewDungeon()
{
	if (dungeon != nullptr)
		delete dungeon;

	int width = getInputInt("Width: ", 2, 10);
	int height = getInputInt("Height: ", 2, 10);
	int depth = getInputInt("Depth: ", 2, 10);

	dungeon = new Dungeon(width, height, depth);
}

void Application::createNewPlayer()
{
	if (dungeon != nullptr)
	{
		if (player != nullptr)
			delete player;

		StringClass name(getInputString("Enter your name: ", 1, 15));
		player = new Player(name.getCharArray(), *dungeon);
	}
	else
		std::cout << "You don't have a dungeon for a new player yet!" << std::endl << std::endl;
}

void Application::createCustomPlayer()
{

}

void Application::displayOptions()
{
	switch (gameState)
	{
		case 0:
			std::cout << "Choose one of the following options:" << std::endl;
			std::cout << "- 1: Create dungeon (new player)" << std::endl;
			std::cout << "- 2: Create dungeon (load player)" << std::endl;
			std::cout << "- 3: Quit" << std::endl << std::endl;
			break;
		case 1:
			std::cout << "Choose one of the following options:" << std::endl;
			std::cout << "- 1: Fight" << std::endl;
			std::cout << "- 2: Run" << std::endl;
			std::cout << "- 3: Rest" << std::endl;
			std::cout << "- 4: Pick up item" << std::endl;
			std::cout << "- 5: Show inventory" << std::endl;
			std::cout << "- 6: Show map" << std::endl;
			std::cout << "- 7: Show stats" << std::endl;
			std::cout << "- 8: Quit" << std::endl << std::endl;
			break;
		case 2:
			std::cout << "Choose one of the following options:" << std::endl;
			std::cout << "- 1: Attack" << std::endl;
			std::cout << "- 2: Run" << std::endl;
			std::cout << "- 3: Use item" << std::endl << std::endl;
			break;
	}
}

int Application::handleUserInput()
{
	switch (gameState)
	{
		case 0: return getInputInt("Option: ", 1, 3);
		case 1: return getInputInt("Action: ", 1, 8);
		case 2: return getInputInt("Action: ", 1, 3);
	}
}

void Application::handleOptions(int option)
{
	switch (gameState)
	{
		case 0:
			switch (option)
			{
				case 1:
					createNewDungeon();
					createNewPlayer();
					gameState = 1;
					break;
				case 2:
					createNewDungeon();
					createCustomPlayer();
					gameState = 1;
					break;
				case 3:
					running = false;
					break;
			}
			break;
		case 1:
			switch (option)
			{
				case 1: gameState = 2; break;
				case 2: player->run(); break;
				case 3: player->rest(); break;
				case 4: player->pickUpItem(); break;
				case 5: player->displayInventory(); break;
				case 6: player->displayCurrentLayer(); break;
				case 7: player->displayStats(); break;
				case 8: gameState = 0; break;
			}
			break;
		case 2:
			switch (option)
			{
				case 1: player->fight(); break;
				case 2: player->run(); 
						gameState = 1; break;
				case 3: player->useItem(); break;
			}
			break;
	}
}