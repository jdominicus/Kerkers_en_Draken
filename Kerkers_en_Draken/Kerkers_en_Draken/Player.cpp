#include "Player.h"
#include "Item.h"
#include "Room.h"
#include "Layer.h"
#include "Dungeon.h"
#include "StringClass.h"
#include "RandomNumberGenerator.h"

#include <iostream>

Player::Player(const char* name, Dungeon& dungeon) : Player(name, 1, 0, 10, 10, 10, 10, dungeon)
{
}

Player::Player(const char* name, int level, int experience, int hitpoints, int maxHitpoints, int attack, int defence, Dungeon& dungeon)
	: name{ new StringClass(name) }, level{ level }, experience{ experience }, hitpoints{ hitpoints }, maxHitpoints{ maxHitpoints }, 
	attack{ attack }, defence{ defence }, dungeon{ &dungeon }
{
	currentLayer = dungeon.getLayer(0);
	currentRoom = dungeon.getStartRoom();
	currentRoom->setVisited();
}

Player::~Player()
{
	for (int i = 0; i < INV_SPACE; i++)
		if (inventory[i] != nullptr)
			delete inventory[i];

	delete name;
}

Room* Player::getCurrentRoom() const
{
	return this->currentRoom;
}

Layer* Player::getLayer() const
{
	return this->currentLayer;
}

void Player::pickUpItem()
{
	if (currentRoom != nullptr && currentRoom->getItem() != nullptr)
	{
		for (int i = 0; i < INV_SPACE; i++)
			if (inventory[i] == nullptr)
			{
				inventory[i] = currentRoom->getItem();
				currentRoom->removeItem();
				std::cout << "You pick up the " << inventory[i]->getName() << "!" << std::endl << std::endl;
				return;
			}

		std::cout << "Your inventory is full!" << std::endl << std::endl;
	}
	else
		std::cout << "There is no item in this room!" << std::endl << std::endl;
}

void Player::useItem()
{
	bool hasItem = false;
	for (int i = 0; i < INV_SPACE; i++)
		if (inventory[i] != nullptr)
			hasItem = true;

	if (!hasItem)
	{
		std::cout << "You don't have any items in your inventory!" << std::endl << std::endl;
		return;
	}

	std::cout << "Choose a item:" << std::endl;

	for (int i = 0; i < INV_SPACE; i++)
	{
		if (inventory[i] != nullptr)
			std::cout << "-" << i + 1 << ": " << inventory[i]->getName() << std::endl;
		else
			std::cout << "-" << i + 1 << ": Empty" << std::endl;
	}

	int item = getInputInt("Item: ", 1, 5);
	while (inventory[item - 1] == nullptr)
	{
		std::cout << "You can't use this item!" << std::endl;
		item = getInputInt("Item: ", 1, 5);
	}

	std::cout << std::endl;
	inventory[item - 1]->use(*this);
	delete inventory[item - 1];
	inventory[item - 1] = nullptr;
	std::cout << std::endl;
}

void Player::rest()
{
	RandomNumberGenerator* random = RandomNumberGenerator::getRandom();
	int hitpoints = random->getNumber(1, 5);
	this->hitpoints = this->hitpoints + hitpoints;

	int totalHeal = this->hitpoints > maxHitpoints ? hitpoints - (this->hitpoints - maxHitpoints) : hitpoints;
	this->hitpoints = this->hitpoints > maxHitpoints ? maxHitpoints : this->hitpoints;

	std::cout << "You start to rest and heal " << totalHeal << " hitpoints!" << std::endl;

	if (currentRoom->getMonster() == nullptr && random->getBool(50))
	{
		std::cout << "A new monster appeared in the room while you were resting..." << std::endl;
	}

	std::cout << std::endl;
}

void Player::fight()
{

}

void Player::run()
{
	std::cout << "Choose a direction:" << std::endl;
	std::cout << "- 1: North" << std::endl;
	std::cout << "- 2: East" << std::endl;
	std::cout << "- 3: South" << std::endl;
	std::cout << "- 4: West" << std::endl;
	std::cout << "- 5: Staircase up" << std::endl;
	std::cout << "- 6: Staircase down" << std::endl;

	int direction = getInputInt("Direction: ", 1, 6) - 1;
	while (currentRoom->getRoom(direction) == nullptr)
	{
		std::cout << "You can't go in this direction!" << std::endl;
		direction = getInputInt("Direction: ", 1, 6) - 1;
	}
		
	currentRoom->destroyMonster();
	currentRoom = currentRoom->getRoom(direction);
	currentRoom->setVisited();
	currentRoom->setMonster();
	currentLayer = currentRoom->getLayer();
	std::cout << std::endl;
}

void Player::addExperience(int experience)
{
	this->experience = this->experience + experience;

	while (this->experience >= 100)
	{
		this->experience = this->experience - 100;
		this->level++;
		this->maxHitpoints += 10;
	}
}

void Player::changeStats(int hitpoints, int attack, int defence)
{
	this->hitpoints = this->hitpoints + hitpoints;
	this->attack = this->attack + attack;
	this->defence = this->defence + defence;

	if (hitpoints > maxHitpoints)
		hitpoints = maxHitpoints;
}

void Player::displayStats() const
{
	std::cout << "Player: " << this->name->getCharArray() << std::endl;
	std::cout << "Level: " << this->level << std::endl;
	std::cout << "Experience: " << this->experience << "/100" << std::endl;
	std::cout << "Hitpoints: " << this->hitpoints << "/"<< this->maxHitpoints << std::endl;
	std::cout << "Attack: " << this->attack << std::endl;
	std::cout << "Deffence: " << this->defence << std::endl << std::endl;
}

void Player::displayInventory() const
{
	std::cout << "Inventory:" << std::endl;

	for (int i = 0; i < INV_SPACE; i++)
	{
		if (inventory[i] != nullptr)
			std::cout << "- " << i << ": " << inventory[i]->getName() << std::endl;
		else
			std::cout << "- " << i << ": Empty" << std::endl;
	}

	std::cout << std::endl;
}

void Player::displayCurrentLayer() const
{
	currentLayer->print();
}