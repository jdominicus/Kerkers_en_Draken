#include "Layer.h"
#include "Room.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Layer::Layer(int width, int height, int minLevelMonsters, int maxLevelMonsters, Dungeon* dungeon, RandomNumberGenerator* random) 
	: width{ width }, height{ height }, minLevelMonsters{ minLevelMonsters }, maxLevelMonsters{ maxLevelMonsters }, dungeon{ dungeon }, random{ random }
{
	rooms = new Room*[width * height];
	for (int i = 0; i < (width * height); i++)
		rooms[i] = new Room(random, this);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < (width - 1); j++)
		{
			Room* firstRoom = rooms[i * width + j];
			Room* secondRoom = rooms[i * width + j + 1];
			firstRoom->setRoom(1, secondRoom);
			secondRoom->setRoom(3, firstRoom);
		}
	}

	for (int i = 0; i < (height - 1); i++)
	{
		for (int j = 0; j < width; j++)
		{
			Room* firstRoom = rooms[i * width + j];
			Room* secondRoom = rooms[(i + 1) * width + j];
			firstRoom->setRoom(2, secondRoom);
			secondRoom->setRoom(0, firstRoom);
		}
	}
}

Layer::~Layer()
{
	for (int i = 0; i < (width * height); i++)
		delete rooms[i];

	delete[] rooms;
}

int Layer::getMinLevelMonsters()
{
	return this->minLevelMonsters;
}

int Layer::getMaxLevelMonsters()
{
	return this->maxLevelMonsters;
}

Room* Layer::getStartRoom()
{
	return this->startRoom;
}

void Layer::setStartRoom(int index)
{
	if (index >= 0 && index <= (width * height - 1))
	{
		rooms[index]->setStartRoom();
		startRoom = rooms[index];
	}
}

Room* Layer::getEndRoom()
{
	return this->endRoom;
}

void Layer::setEndRoom(int index)
{
	if (index >= 0 && index <= (width * height - 1))
	{
		rooms[index]->setEndRoom();
		endRoom = rooms[index];
	}
}

Room* Layer::getRooms(int index)
{
	if (index >= 0 && index <= (width * height - 1))
		return rooms[index];
	else
		return nullptr;
}

void Layer::print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Room* currentRoom = rooms[i * width + j];
			Room* nextRoom = currentRoom->getRoom(1);
			std::cout << currentRoom->getRoomType();

			if (nextRoom != nullptr && (currentRoom->isVisited() || nextRoom->isVisited()))
				std::cout << "-";
			else
				std::cout << " ";
		}

		std::cout << std::endl;

		for (int j = 0; j < width; j++)
		{
			Room* currentRoom = rooms[i * width + j];
			Room* nextRoom = currentRoom->getRoom(2);

			if (nextRoom != nullptr && (currentRoom->isVisited() || nextRoom->isVisited()))
				std::cout << "| ";
			else
				std::cout << "  ";
		}

		std::cout << std::endl;
	}
}
