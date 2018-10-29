#include "Monster.h"

Monster::Monster(char name[], int level, int attack, int nrOfAttacks,
	int strengthMin, int strengthMax, int defence, int hp)
	:level{ level }, attack{ attack }, nrOfAttacks{ nrOfAttacks }, strengthMin{ strengthMin },
	strengthMax{ strengthMax }, defence{ defence }, hp{ hp }
{
	for (int i = 0; i < 30; i++)
	{
		this->name[i] = name[i];
	}
}

Monster::~Monster()
{
}
