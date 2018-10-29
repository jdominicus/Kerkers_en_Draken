#include "Layer.h"
#include "Room.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Layer::Layer(int width, int height, Dungeon& dungeon, int layerLevel) 
	: width{ width }, height{ height }, dungeon{ &dungeon }, 
	layerLevel{ layerLevel }, startRoom{ nullptr }, endRoom{ nullptr }
{
	RandomNumberGenerator* random = RandomNumberGenerator::getRandom();

	rooms = new Room*[width * height];
	for (int i = 0; i < (width * height); i++)
	{
		try
		{
			rooms[i] = new Room(*this);
			if (rooms[i] == nullptr)
				throw 0;
		}
		catch (int error)
		{
			for (int j = 0; j < i; j++)
				delete rooms[j];

			std::cout << "Failed to allocate new Rooms!" << std::endl;
			throw 0;
		}
	}
		
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

int Layer::getLayerLevel() const
{
	return this->layerLevel;
}

Room* Layer::getStartRoom() const
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

Room* Layer::getEndRoom() const
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

Room* Layer::getRooms(int index) const
{
	return (index >= 0 && index <= (width * height - 1) ? rooms[index] : nullptr);
}

void Layer::print() const
{
	std::cout << "Layer: " << layerLevel << std::endl;
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

Room* Layer::getDungeonEndRoom() const
{
	return dungeon->getEndRoom();
}
