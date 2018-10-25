#include "Player.h"
#include "Item.h"
#include "Room.h"
#include "Layer.h"
#include "Dungeon.h"
#include "StringClass.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Player::Player(const char* name, int level, int hitpoints, int experience, int attack, int deffence, Dungeon* dungeon)
	: name{ new StringClass(name) }, level{ level }, hitpoints{ hitpoints }, experience{ experience }, attack{ attack }, 
	deffence{ deffence }, dungeon{ dungeon }
{
	currentLayer = dungeon->getLayer(0);
	currentRoom = dungeon->getStartRoom();
	currentRoom->setVisited();
}

Player::~Player()
{
	for (int i = 0; i < 5; i++)
		if (inventory[i] != nullptr)
			delete inventory[i];

	delete name;
}

Layer* Player::getLayer()
{
	return this->currentLayer;
}

void Player::pickUpItem()
{
	if (currentRoom != nullptr && currentRoom->getItem() != nullptr)
	{
		for (int i = 0; i < 5; i++)
		{
			if (inventory[i] == nullptr)
			{
				inventory[i] = new Item(std::move(*currentRoom->getItem()));
				break;
			}
		}
	}
}

void Player::move(int direction)
{
	if (currentRoom->getRoom(direction) != nullptr)
	{
		currentRoom->destroyMonster();
		currentRoom = currentRoom->getRoom(direction);
		currentRoom->setVisited();
		currentLayer = currentRoom->getLayer();
	}
}

void Player::displayCurrentRoom()
{
	std::cout << currentRoom->getDescription()->getCharArray() << std::endl;
}

void Player::displayCurrentLayer()
{
	currentLayer->print();
}