#pragma once
#include "Monster.h"
#include "RandomNumberGenerator.h"

class MonsterFactory
{
public:
	~MonsterFactory();

private:
	static MonsterFactory* mF;

	Monster** optionalMonsters;
	int nrOfMonsters;

public:
	static MonsterFactory* getMF();
	static void removeMF();

	Monster* createMonster(char info[]);
	Monster* getBoss()const;

private:
	MonsterFactory();
};

