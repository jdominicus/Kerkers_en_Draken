#include "Monster.h"
#include "StringClass.h"

Monster::Monster(StringClass* name, int level, int attack, int nrOfAttacks, int strengthMin, int strengthMax, int defence, int hp)
	: name{ name }, level{ level }, attack{ attack },
	nrOfAttacks{ nrOfAttacks }, strengthMin{ strengthMin }, strengthMax{ strengthMax }, defence{ defence }, hp{ hp }
{
}

Monster::~Monster()
{
	delete name;
}

Monster::Monster(const Monster& other) : level{ other.level }, attack{ other.attack }, nrOfAttacks{ other.nrOfAttacks }, strengthMin{ other.strengthMin },
strengthMax{ other.strengthMax }, defence{ other.defence }, hp{ other.hp }
{
	this->name = new StringClass(*(other.name));
}

const char* Monster::getName() const
{
	return this->name->getCharArray();
}

int Monster::getLevel() const
{
	return level;
}

void Monster::reduceHealth(int health)
{
	this->hp = this->hp - health;
	if (health < 0)
		this->hp = 0;
}

int Monster::getHealth() const
{
	return this->hp;
}

int Monster::getAttack() const
{
	return this->attack;
}

int Monster::getNrOfAttacks() const
{
	return this->nrOfAttacks;
}

int Monster::getStrenghtMin() const
{
	return this->strengthMin;
}

int Monster::getStrenghtMax() const
{
	return this->strengthMax;
}

int Monster::getDefence() const
{
	return this->defence;
}

