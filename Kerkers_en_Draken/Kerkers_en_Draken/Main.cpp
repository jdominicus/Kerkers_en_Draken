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
		RandomNumberGenerator* random = new RandomNumberGenerator();
		Dungeon* dungeon = new Dungeon(5, 3, 3, random);
		Player* player = new Player("Jordy", 1, 10, 0, 1, 1, dungeon);

		while (true)
		{
			player->getLayer()->print();
			player->displayCurrentRoom();
			int option;
			std::cin >> option;
			player->move(option);
		}

		getchar();
		delete random;
		delete dungeon;
		delete player;
	}

	_CrtDumpMemoryLeaks();
}
