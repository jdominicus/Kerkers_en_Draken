#include "Application.h"
#include "Dungeon.h"
#include "Room.h"
#include "Player.h"
#include "StringClass.h"
#include "MonsterFactory.h"
#include "RandomNumberGenerator.h"
#include "FileHandler.h"
#include "Item.h"

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
	MonsterFactory::removeMF();
}

void Application::start()
{
	while (running)
	{
		displayOptions();
		int input = handleUserInput();
		std::cout << std::endl;
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

	try
	{
		dungeon = new Dungeon(width, height, depth);
		if (dungeon == nullptr)
			throw 0;
	}
	catch (int error)
	{
		std::cout << "Failed to allocate new Dungeon!" << std::endl;
	}
}

void Application::createNewPlayer()
{
	this->gameState = 1;
	if (player != nullptr)
		delete player;

	StringClass name(getInputString("Enter your name: ", 1, 15));
	
	try
	{
		if (dungeon == nullptr)
			throw 0;

		player = new Player(name.getCharArray(), *dungeon);
		if (player == nullptr)
			throw 1;
	}
	catch (int error)
	{
		gameState = 0;
		switch (error)
		{
			case 0: 
				std::cout << "No Dungeon to allocate new Player!" << std::endl; break;
			case 1:
				delete dungeon;
				std::cout << "Failed to allocate new Player!" << std::endl; break;
		}
	}
	
	std::cout << std::endl;
}

void Application::loadPlayer()
{

}

void Application::savePlayer()
{
	FileHandler* fH = new FileHandler();
	StringClass* temp = new StringClass("");
	temp = player->getName();
	for (int i = 0; i < 5; i++)
	{
		fH->writeInfo(player->getAttributes(i) + 48);
	}
	for (int i = 0; i < INV_SPACE; i++)
	{
		c = player->getInventory(i)->getId() + 48;
		temp->append(c);
		temp->append(player->getInventory(i)->getName());
		fH->writeInfo();
		delete temp;
	}
	delete fH;
}

void Application::displayOptions() const
{
	switch (gameState)
	{
		case 0:
			std::cout << "Choose one of the following options:" << std::endl;
			std::cout << "- 1: Create dungeon (new player)" << std::endl;
			std::cout << "- 2: Create dungeon (load player)" << std::endl;
			std::cout << "- 3: Quit" << std::endl;
			break;
		case 1:
			player->getCurrentRoom()->print();
			std::cout << "Choose one of the following options:" << std::endl;
			std::cout << "- 1: Fight" << std::endl;
			std::cout << "- 2: Run" << std::endl;
			std::cout << "- 3: Rest" << std::endl;
			std::cout << "- 4: Pick up item" << std::endl;
			std::cout << "- 5: Show inventory" << std::endl;
			std::cout << "- 6: Show map" << std::endl;
			std::cout << "- 7: Show stats" << std::endl;
			std::cout << "- 8: Quit" << std::endl;
			break;
		case 2:
			std::cout << "Choose one of the following options:" << std::endl;
			std::cout << "- 1: Attack" << std::endl;
			std::cout << "- 2: Run" << std::endl;
			std::cout << "- 3: Use item" << std::endl;
			break;
	}
}

int Application::handleUserInput() const
{
	switch (gameState)
	{
		case 0: return getInputInt("Option: ", 1, 3);
		case 1: return getInputInt("Action: ", 1, 8);
		case 2: return getInputInt("Action: ", 1, 3);
		default: return 0;
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
					break;
				case 2:
					createNewDungeon();
					loadPlayer();
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
				case 8:
					gameState = 0;
					savePlayer();
					break;
			}
			break;
		case 2:
			switch (option)
			{
				case 1: player->fight(); 
					if (player->getHealth() == 0)
						gameState = 0;
						break;
				case 2: player->run(); 
						gameState = 1; break;
				case 3: player->useItem(); break;
			}
			break;
	}
}
