#include "Dungeon.h"
#include "Layer.h"
#include "Room.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Dungeon::Dungeon(int width, int height, int depth) : width{ width }, height{ height }, depth{ depth }
{
	RandomNumberGenerator* random = RandomNumberGenerator::getRandom();

	layers = new Layer*[depth];
	for (int i = 0; i < depth; i++)
	{
		try
		{
			layers[i] = new Layer(width, height, *this, i+1);
			if (layers[i] == nullptr)
				throw 0;
		}
		catch (int error)
		{
			for (int j = 0; j < i; j++)
				delete layers[j];

			std::cout << "Failed to allocate new Layers!" << std::endl;
			throw 0;
		}	
	}
		
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

	this->startRoom = layers[0]->getStartRoom();
	this->endRoom = layers[depth - 1]->getEndRoom();
}

Dungeon::~Dungeon()
{
	for (int i = 0; i < depth; i++)
		delete layers[i];

	delete[] layers;
}

Layer* Dungeon::getLayer(int index) const
{
	if (index >= 0 && index <= (depth - 1))
		return layers[index];
	else
		return nullptr;
}

Room* Dungeon::getStartRoom() const
{
	return this->startRoom;
}

Room* Dungeon::getEndRoom() const
{
	return this->endRoom;
}

void Dungeon::print() const
{
	for (int i = 0; i < depth; i++)
	{
		std::cout << "Layer: " << i << std::endl;
		if (layers[i] != nullptr)
			layers[i]->print();
	}
}
