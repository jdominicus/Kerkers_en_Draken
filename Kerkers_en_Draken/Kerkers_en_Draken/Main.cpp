#include "RandomNumberGenerator.h"
#include "StringClass.h"
#include "Room.h"
#include "Layer.h"
#include "Dungeon.h"
#include "Player.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <iostream>

int main()
{
	{
		Dungeon* dungeon = new Dungeon(5, 3, 3);
		Player* player = new Player("Jordy", 1, 10, 0, 1, 1, *dungeon);

		int input = 0;
		while (input < 9)
		{
			player->getLayer()->print();
			std::cin >> input;
			player->move(input);
			player->pickUpItem();
			player->displayInventory();
		}

		delete dungeon;
		delete player;

		RandomNumberGenerator::removeRandom();
	}

	_CrtDumpMemoryLeaks();
}
