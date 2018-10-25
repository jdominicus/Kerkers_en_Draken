#include "RandomNumberGenerator.h"
#include "StringClass.h"
#include "Room.h"
#include "Layer.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <iostream>

int main()
{
	{
		RandomNumberGenerator* random = new RandomNumberGenerator();
		Layer* layer = new Layer(5, 5, 1, 2, nullptr, random);

		layer->print();
		getchar();
		delete random;
		delete layer;
	}

	_CrtDumpMemoryLeaks();
}
