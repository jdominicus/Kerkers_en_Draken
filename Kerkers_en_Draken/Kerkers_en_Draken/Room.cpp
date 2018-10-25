#include "Room.h"
#include "Item.h"
#include "Monster.h"
#include "Layer.h"
#include "StringClass.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Room::Room(RandomNumberGenerator* random, Layer* layer) 
	: layer{ layer }, startRoom{ false }, endRoom{ false }, visited{ false }, roomType{ '.' }, description{ nullptr }, rooms{}, random{ random }
{
	clean = random->getNumber(0, 1);
	size = random->getNumber(1, 3);
	layout = random->getNumber(1, 3);
	
	createDescription();
	createItem();
	createMonster();
}

Room::~Room()
{
	if (monster)
		delete this->monster;
	if (item)
		delete this->item;
	
	delete this->description;
}

void Room::setStartRoom()
{
	this->endRoom = false;
	this->startRoom = true;
}

void Room::setEndRoom()
{
	this->startRoom = false;
	this->endRoom = true;
}

void Room::setVisited()
{
	this->visited = true;

	if (startRoom)
		this->roomType = 'S';
	else if (endRoom)
		this->roomType = 'E';
	else
		this->roomType = 'N';
}

bool Room::isVisited()
{
	return this->visited;
}

char Room::getRoomType()
{
	return this->roomType;
}

Room* Room::getRoom(int index)
{
	if (index >= 0 && index <= 5)
		return rooms[index];
	else
		return nullptr;
}

void Room::setRoom(int index, Room* room)
{
	if (index >= 0 && index <= 5)
		rooms[index] = room;
}

void Room::createDescription()
{
	description = new StringClass("Het is een ");

	switch (size)
	{
		case 1: description->append("kleine "); break;
		case 2: description->append("gemiddelde "); break;
		case 3: description->append("grote ");  break;
	}

	switch (clean)
	{
		case 0: description->append("smerige "); break;
		case 1: description->append("opgeruimde "); break;
	}

	description->append("kamer. ");

	switch (layout)
	{
		case 1: description->append("De kamer is leeg."); break;
		case 2: description->append("In de hoek staat een bed."); break;
		case 3: description->append("Er staat een tafel met vier stoelen.");  break;
	}
}

void Room::createItem()
{
	if (random->getBool(50))
	{
		switch (random->getNumber(1, 5))
		{
			case 1: item = new Item(); break;
			case 2: item = new Item(); break;
			case 3: item = new Item(); break;
			case 4: item = new Item(); break;
			case 5: item = new Item(); break;
		}
	}
	else
	{
		item = nullptr;
	}
}

void Room::createMonster()
{
	if (random->getBool(50))
	{
		switch (random->getNumber(0, 5))
		{
			case 1:	break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: break;
			case 8: break;
			case 9: break;
		}
	}
	else
	{
		monster = nullptr;
	}
}

void Room::printDescription()
{
	std::cout << description->getCharArray() << std::endl;
}
