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

void Player::displayStats()
{
	std::cout << "Player: " << this->name->getCharArray() << std::endl;
	std::cout << "Level: " << this->level << std::endl;
	std::cout << "Experience: " << this->experience << "/100" << std::endl;
	std::cout << "Hitpoints: " << this->hitpoints << "/"<< this->maxHitpoints << std::endl;
	std::cout << "Attack: " << this->attack << std::endl;
	std::cout << "Deffence: " << this->defence << std::endl << std::endl;
}

void Player::displayInventory()
{
	std::cout << "Inventory:" << std::endl;

	for (int i = 0; i < 5; i++)
	{
		std::cout << "- " << i << ": ";

		if (inventory[i] != nullptr)
			std::cout << inventory[i]->getName() << std::endl;
		else
			std::cout << "Empty" << std::endl;
	}

	std::cout << std::endl;
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