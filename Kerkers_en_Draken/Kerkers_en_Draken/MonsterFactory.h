#pragma once
#include "Monster.h"

class MonsterFactory
{
public:
	MonsterFactory();
	~MonsterFactory();

private:
	Monster** optionalMonsters;
	int nrOfMonsters;
	void resize();

public:
	void addMonster(char info[]);
	Monster* createMonster(char info[]);
};

