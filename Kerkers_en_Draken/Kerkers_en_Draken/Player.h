#pragma once

class Item;

class Player
{
	public:
		Player(char* name);
		~Player();

	private:
		const char name[15];
		int level;
		int hitpoints;
		int experience;
		int attack;
		int deffence;
		Item* inventory[];
};

