#include "RandomNumberGenerator.h"
#include "StringClass.h"
#include "Room.h"
#include "Layer.h"
#include "Dungeon.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <iostream>

int main()
{
	{
		RandomNumberGenerator* random = new RandomNumberGenerator();
		Dungeon* dungeon = new Dungeon(10, 5, 10, random);
		dungeon->print();

		getchar();
		delete random;
	}

	_CrtDumpMemoryLeaks();
}
