#include "Player.h"
#include "Item.h"
#include "Room.h"
#include "Layer.h"
#include "Dungeon.h"
#include "StringClass.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Player::Player(const char* name, int level, int hitpoints, int experience, int attack, int defence, Dungeon& dungeon)
	: name{ new StringClass(name) }, level{ level }, hitpoints{ hitpoints }, experience{ experience }, attack{ attack }, 
	defence{ defence }, dungeon{ &dungeon }
{
	currentLayer = dungeon.getLayer(0);
	currentRoom = dungeon.getStartRoom();
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
			if (inventory[i] == nullptr)
			{
				inventory[i] = currentRoom->getItem();
				currentRoom->removeItem();
				return;
			}

		std::cout << "Your inventory is full!" << std::endl;
		std::cout << std::endl;
	}
}

void Player::useItem(int index)
{
	if (index >= 0 && index <= 4 && inventory[index] != nullptr)
	{
		inventory[index]->use(*this);
		delete inventory[index];
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

void Player::addExperience(int experience)
{
	this->experience = this->experience + experience;

	while (this->experience >= 100)
	{
		this->experience = this->experience - 100;
		this->level++;
	}
}

void Player::changeStats(int hitpoints, int attack, int defence)
{
	this->hitpoints = this->hitpoints + hitpoints;
	this->attack = this->attack + attack;
	this->defence = this->defence + defence;
}

void Player::displayStats()
{
	std::cout << "Level: " << this->level << std::endl;
	std::cout << "Experience: " << this->experience << "/100" << std::endl;
	std::cout << "Hitpoints: " << this->hitpoints << std::endl;
	std::cout << "Attack: " << this->attack << std::endl;
	std::cout << "Deffence: " << this->defence << std::endl;
	std::cout << std::endl;
}

void Player::displayInventory()
{
	std::cout << "Inventory:" << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << i << ":";

		if (inventory[i] != nullptr)
			std::cout << inventory[i]->getName() << std::endl;
		else
			std::cout << "Empty" << std::endl;
	}
}

void Player::displayCurrentRoom()
{
	std::cout << currentRoom->getDescription()->getCharArray() << std::endl;
	std::cout << std::endl;
}

void Player::displayCurrentLayer()
{
	currentLayer->print();
}