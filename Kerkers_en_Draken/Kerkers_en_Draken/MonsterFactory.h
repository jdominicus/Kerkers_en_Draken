#pragma once
#include "Monster.h"
#include "FileHandler.h"
#include "RandomNumberGenerator.h"

#define NR_OFMONSTERS 14

class MonsterFactory
{
public:
	~MonsterFactory();

private:
	static MonsterFactory* mF;
	Monster* optionalMonsters[NR_OFMONSTERS];

public:
	static MonsterFactory* getMF();
	static void removeMF();

	Monster* createMonster(char info[]);
	Monster* getBoss() const;
	Monster* getMonster(int layer) const;

private:
	MonsterFactory();
};

/*

#pragma once
#include "Monster.h"
#include "FileHandler.h"

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


*/
