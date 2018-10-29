#include "Item.h"
#include "Player.h"
#include "StringClass.h"

#include <iostream>

Item::Item(int id, const char* name) : id{ id }, name{ new StringClass(name) }
{
}

Item::~Item()
{
	delete name;
}

void Item::use(Player& player)
{
	switch (this->id) 
	{
		case 0: player.changeStats(10, 0, 0); 
				std::cout << "You drink the potion... It heals 10 hitpoints!" << std::endl;
				break;
		case 1: player.changeStats(5, 0, 0); 
				std::cout << "You drink the potion... It heals 5 hitpoints!" << std::endl;
				break;
		case 2: player.changeStats(0, 5, 0); 
				std::cout << "You equip the sword and it increases your attack by 5!" << std::endl;
				break;
		case 3: player.changeStats(0, 10, 0); 
				std::cout << "You equip the amulet and it increases your attack by 10!" << std::endl;
				break;
		case 4: player.changeStats(0, 0, 10); 
				std::cout << "You equip the shield and it increases your defence by 10!" << std::endl;
				break;
	}
}

const char* Item::getName() const
{
	return this->name->getCharArray();
}

int Item::getId() const
{
	return id;
}
