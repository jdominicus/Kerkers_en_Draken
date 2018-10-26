#pragma once
#include "Monster.h"

#define NR_OFMONSTERS 14

class MonsterFactory
{
public:
	MonsterFactory();
	~MonsterFactory();

private:
	Monster* optionalMonsters[NR_OFMONSTERS];

public:
	void addMonster(char info[]);
	Monster* createMonster(char info[]);
};

