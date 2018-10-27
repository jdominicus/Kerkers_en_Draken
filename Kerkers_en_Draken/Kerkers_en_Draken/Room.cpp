#include "Room.h"
#include "Item.h"
#include "Monster.h"
#include "Layer.h"
#include "StringClass.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Room::Room(Layer& layer) 
	: layer{ &layer }, startRoom{ false }, endRoom{ false }, visited{ false }, roomType{ '.' }, monster{ nullptr }
{
	RandomNumberGenerator* random = RandomNumberGenerator::getRandom();
	clean = random->getNumber(0, 1);
	size = random->getNumber(1, 3);
	layout = random->getNumber(1, 3);
	
	createDescription();
	createItem();
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

StringClass* Room::getDescription()
{
	return this->description;
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

Item* Room::getItem()
{
	return this->item;
}

void Room::removeItem()
{
	this->item = nullptr;
}

Monster* Room::getMonster() 
{
	return this->monster;
}

void Room::destroyMonster()
{
	if (monster != nullptr)
		delete monster;
}

Layer* Room::getLayer()
{
	return this->layer;
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
	RandomNumberGenerator* random = RandomNumberGenerator::getRandom();

	if (random->getBool(50))
	{
		switch (random->getNumber(1, 5))
		{
			case 1: item = new Item(0, "HP Potion (10)"); break;
			case 2: item = new Item(1, "HP Potion (5)"); break;
			case 3: item = new Item(2, "Sword"); break;
			case 4: item = new Item(3, "Amulet"); break;			
			case 5: item = new Item(4, "Shield"); break;
		}
	}
	else
		item = nullptr;
}
