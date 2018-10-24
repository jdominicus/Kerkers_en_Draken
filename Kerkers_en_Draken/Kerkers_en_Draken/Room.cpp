#include "Room.h"
#include "Item.h"
#include "Monster.h"

Room::Room(std::default_random_engine generator)
{
	std::uniform_int_distribution<int> distribution_1(0, 1);
	clean = distribution_1(generator);

	std::uniform_int_distribution<int> distribution_2(1, 3);
	size = distribution_2(generator);
	layout = distribution_2(generator);
}

Room::~Room()
{
}
