#pragma once

#include <Random>
#include <ctime>

class Item;
class Monster;

class Room
{
	public:
		Room(std::default_random_engine generator);
		~Room();

	private:
		bool clean;
		int layout;
		int size;
		char* description;

		Item* item;
		Monster* monster;
};

