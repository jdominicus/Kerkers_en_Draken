#include "MonsterFactory.h"
#include "StringClass.h"

MonsterFactory* MonsterFactory::mF = nullptr;

MonsterFactory::MonsterFactory()
{
	FileHandler* fh = new FileHandler();
	fh->openMonsterFile();

	for (int i = 0; i < NR_OFMONSTERS; i++)
		optionalMonsters[i] = createMonster(fh->readInfo());

	fh->closeFile();
	delete fh;
}

MonsterFactory::~MonsterFactory()
{
	for (int i = 0; i < NR_OFMONSTERS; i++)
		delete optionalMonsters[i];
}

MonsterFactory* MonsterFactory::getMF()
{
	if (mF == nullptr)
		mF = new MonsterFactory();

	return mF;
}

void MonsterFactory::removeMF()
{
	if (mF != nullptr)
		delete mF;
}

Monster* MonsterFactory::createMonster(char info[])
{
	char name[30] = "+++++++++++++++++++++++++++++";				//naam max 30 characters
	int level = 0;				//1-10 gevaarlijkheid / 25 voor eindbaas
	int attack = 0;				//0-100 percentage voor hitrate
	int nrOfAttacks = 0;		//1-9 aantal keren dat het monster aanvalt
	int strengthMin = 0;		//0-9 minimum schadepunten
	int strengthMax = 0;		//1-99 maximum schadepunten
	int defence = 0;			//10-99 percentage voor ontwijken
	int hp = 0;					//1-999 levenspunten

	int attribute = 0;

	for (int i = 0; i < lineLength; i++)
	{
		if (info[i] == ';')
		{
			attribute++;
			i++;
		}
		if (info[i] == ']')
		{
			attribute = 8;
		}

		switch (attribute)
		{
		case(0):	//name
			name[i] = info[i];
			if (info[i + 1] == ';')
			{
				name[i + 1] = '\0';
			}
			break;
		case(1):	//level
			if (info[i] == 'B')
			{
				level = 25;
				attribute++;
				i = i + 4;
			}
			else if (info[i + 1] != ';')
			{
				level = 10;
				attribute++;
				i = i + 2;
			}
			else
			{
				level = info[i] - 48;	//begin of numbers in ASCII
			}
			break;
		case(2):	//attack
			int attack1, attack2;
			attack1 = info[i] - 48;
			if (info[i + 1] != 'x')
			{
				attack2 = info[i + 1] - 48;
				if (info[i + 2] != 'x')
				{
					attack = 100;
					i = i + 3;
					attribute++;
				}
				else
				{
					attack = (attack1 * 10) + attack2;
					i = i + 2;
					attribute++;
				}
			}
			else
			{
				attack = attack1;
				attribute++;
				i = i + 2;
			}
			break;
		case(3):	//nrOfAttacks (max 9)
			nrOfAttacks = info[i] - 48;
			break;
		case(4):	//strengthMin
			strengthMin = info[i] - 48;
			attribute++;
			i++;
			break;
		case(5):	//strengthMax
			int strength1, strength2;
			strength1 = info[i] - 48;
			if (info[i + 1] != ';')
			{
				strength2 = info[i + 1] - 48;
				strengthMax = (strength1 * 10) + strength2;
				i++;
			}
			else
			{
				strengthMax = strength1;
			}
			break;
		case(6):	//defence
			int defence1, defence2;
			defence1 = info[i] - 48;
			defence2 = info[i + 1] - 48;
			defence = (defence1 * 10) + defence2;
			i++;
			break;
		case(7):	//hp
			int hp1, hp2, hp3;
			hp1 = info[i] - 48;
			if (info[i + 1] != ']')
			{
				hp2 = info[i + 1] - 48;
				if (info[i + 2] != ']')
				{
					hp3 = info[i + 2] - 48;
					hp = (hp1 * 100) + (hp2 * 10) + hp3;
					i = i + 2;
					attribute++;
				}
				else
				{
					hp = (hp1 * 10) + hp2;
					i++;
					attribute++;
				}
			}
			else
			{
				hp = hp1;
				attribute++;
			}
			break;
		case(8):
			break;
		}
	}

	Monster* monster = new Monster(new StringClass(name), level, attack, nrOfAttacks,
		strengthMin, strengthMax, defence, hp);
	return monster;
}

Monster* MonsterFactory::getBoss() const
{
	RandomNumberGenerator* random = RandomNumberGenerator::getRandom();
	if (random->getBool(50))
		return new Monster(*(optionalMonsters[12]));
	else
		return new Monster(*(optionalMonsters[13]));
}

Monster* MonsterFactory::getMonster(int layer) const
{
	RandomNumberGenerator* random = RandomNumberGenerator::getRandom();
	int nr = 0;
	int startPos = 0;
	for (int i = 0; i < NR_OFMONSTERS; i++)
	{
		if (optionalMonsters[i]->getLevel() == layer)
		{
			if (startPos == 0 && layer > 1)
			{
				startPos = i;
			}

			nr++;
		}
	}

	if (random->getBool(50 + layer * 5))
		return new Monster(*(optionalMonsters[startPos + random->getNumber(0, (nr - 1))]));
	else
		return nullptr;
}