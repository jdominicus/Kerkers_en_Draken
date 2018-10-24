#include "Room.h"

#include <iostream>
#include <random>
#include <ctime>

int main()
{
	std::default_random_engine generator;
	generator.seed(time(0));

	Room* room1 = new Room(generator);
	Room* room2 = new Room(generator);
	Room* room3 = new Room(generator);
	int x = 10;

}
