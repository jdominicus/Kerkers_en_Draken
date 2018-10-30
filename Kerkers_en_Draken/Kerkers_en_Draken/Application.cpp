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
	FileHandler* fH = new FileHandler();
	fH->openHeroFile(0);

	char name[15] = "++++++++++++++";
	int level = 0;
	int experience = 0;
	int hitpoints = 0;
	int maxHitpoints = 0;
	int attack = 0;
	int defence = 0;

	int attribute = 0;

	StringClass* hero = new StringClass(fH->readInfo());
	const char* info = hero->getCharArray();

	for (int i = 0; i < hero->getLength(); i++)
	{
		if (info[i] == ';')
		{
			attribute++;
			i++;
		}

		switch (attribute)
		{
		case(0):	//name
			name[i] = info[i];
			if (info[i + 1] == ';')
			{
				name[i + 1] = '\0';
			}
			break;
		case(1):	//level
			int level1, level2;
			level1 = info[i] - 48;
			if (info[i + 1] != ';')
			{
				level2 = info[i + 1] - 48;
				level = (level1 * 10) + level2;
				i++;
			}
			else
			{
				level = level1;
			}
			break;
		case(2):	//experience
			int xp1, xp2, xp3;
			xp1 = info[i] - 48;
			if (info[i + 1] != ';')
			{
				xp2 = info[i + 1] - 48;
				if (info[i + 2] != ';')
				{
					xp3 = info[i + 2] - 48;
					experience = (xp1 * 100) + (xp2 * 10) + xp3;
					i = i + 2;
				}
				else
				{
					experience = (xp1 * 10) + xp2;
					i++;
				}
			}
			else
			{
				experience = xp1;
			}
			break;
		case(3):	//hitpoints
			int hp1, hp2, hp3;
			hp1 = info[i] - 48;
			if (info[i + 1] != ';')
			{
				hp2 = info[i + 1] - 48;
				if (info[i + 2] != ';')
				{
					hp3 = info[i + 2] - 48;
					hitpoints = (hp1 * 100) + (hp2 * 10) + hp3;
					i = i + 2;
				}
				else
				{
					hitpoints = (hp1 * 10) + hp2;
					i++;
				}
			}
			else
			{
				hitpoints = hp1;
			}
			break;
		case(4):	//maxHitpoints
			int mhp1, mhp2, mhp3;
			mhp1 = info[i] - 48;
			if (info[i + 1] != ';')
			{
				mhp2 = info[i + 1] - 48;
				if (info[i + 2] != ';')
				{
					mhp3 = info[i + 2] - 48;
					maxHitpoints = (mhp1 * 100) + (mhp2 * 10) + mhp3;
					i = i + 2;
				}
				else
				{
					maxHitpoints = (mhp1 * 10) + mhp2;
					i++;
				}
			}
			else
			{
				maxHitpoints = mhp1;
			}
			break;
		case(5):	//attack
			int attack1, attack2, attack3;
			attack1 = info[i] - 48;
			if (info[i + 1] != ';')
			{
				attack2 = info[i + 1] - 48;
				if (info[i + 2] != ';')
				{
					attack3 = info[i + 2] - 48;
					attack = (attack1 * 100) + (attack2 * 10) + attack3;
					i = i + 2;
				}
				else
				{
					attack = (attack1 * 10) + attack2;
					i++;
				}
			}
			else
			{
				attack = attack1;
			}
			break;
		case(6):	//defence
			int defence1, defence2;
			defence1 = info[i] - 48;
			defence2 = info[i + 1] - 48;
			defence = (defence1 * 10) + defence2;
			i = i + 2;
			attribute++;
			break;
		case(7):
			break;
		}
	}
	player = new Player(name, level, experience, hitpoints, maxHitpoints, attack, defence, *dungeon);

	fH->closeFile();
	delete hero;
	delete fH;
	std::cout << std::endl << "Hero -" << name << "- loaded!" << std::endl << std::endl;
}

void Application::savePlayer()
{
	FileHandler* fH = new FileHandler();
	fH->openHeroFile(1);
	
	fH->writeInfo("[");
	fH->writeInfo(*player->getName());
	fH->writeInfo(";");
	StringClass* str;
	for (int i = 0; i < 6; i++)
	{
		str = toArray(player->getAttributes(i));
		fH->writeInfo(*str);
		delete str;
		fH->writeInfo(";");
	}
	fH->writeInfo("]");
	std::cout << "The player has left the dungeon and lost his items in the process." << std::endl << std::endl;
	fH->closeFile();
	delete fH;
}

StringClass* Application::toArray(int number)
{
	if (number == 0)
		return new StringClass("0");

	int temp = number;
	int totalCharacters = 0;
	while (number != 0)
	{
		number /= 10;
		totalCharacters++;
	}

	char* array = new char[totalCharacters + 1];
	array[totalCharacters] = '\0';

	for (int i = totalCharacters - 1; i >= 0; i--)
	{
		array[i] = temp % 10 + 48;
		temp /= 10;
	}

	StringClass* string = new StringClass(array);
	delete[] array;
	return string;
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
					if (player->getHealth() <= 0)
						gameState = 0;
					if (dungeon->getEndRoom() == player->getCurrentRoom() && player->getCurrentRoom()->getMonster())
					{
						std::cout << "You won the game!" << std::endl;
						gameState = 8;
					}
					break;
				case 2: player->run(); 
						gameState = 1; break;
				case 3: player->useItem(); break;
			}
			break;
	}
}
