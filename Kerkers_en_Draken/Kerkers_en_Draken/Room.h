#pragma once

class Item;
class Monster;

class Room
{
	public:
		Room();
		~Room();

	private:
		bool clean;
		int layout;
		int size;
		char* description;

		Item* item;
		Monster* monster;
};

