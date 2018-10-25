#include "Dungeon.h"
#include "Layer.h"
#include "Room.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Dungeon::Dungeon(int width, int height, int depth, RandomNumberGenerator* random) : width{ width }, height{ height }, depth{ depth }, random{ random }
{
	layers = new Layer*[depth];
	for (int i = 0; i < depth; i++)
		layers[i] = new Layer(width, height, i, i, this, random);

	int indexStartRoom = random->getNumber(0, (width * height - 1));
	int indexEndRoom = random->getDifferentNumber(0, (width * height - 1), indexStartRoom);
		
	for (int i = 0; i < depth; i++)
	{
		layers[i]->setStartRoom(indexStartRoom);
		layers[i]->setEndRoom(indexEndRoom);

		indexStartRoom = indexEndRoom;
		indexEndRoom = random->getDifferentNumber(0, (width * height - 1), indexStartRoom);
	}

	for (int i = 0; i < (depth - 1); i++)
	{
		Room* endRoom = layers[i]->getEndRoom();
		Room* startRoom = layers[i + 1]->getStartRoom();
		
		endRoom->setRoom(5, startRoom);
		startRoom->setRoom(4, endRoom);
	}

	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < (width * height); j++)
		{
			layers[i]->getRooms(j)->setVisited();
		}
	}
}

Dungeon::~Dungeon()
{
	for (int i = 0; i < depth; i++)
		delete layers[i];

	delete[] layers;
}

Layer* Dungeon::getLayer(int index)
{
	if (index >= 0 && index <= (depth - 1))
		return layers[index];
	else
		return nullptr;
}

void Dungeon::print()
{
	for (int i = 0; i < depth; i++)
	{
		std::cout << "Layer: " << i << std::endl;
		if (layers[i] != nullptr)
			layers[i]->print();
	}
}
