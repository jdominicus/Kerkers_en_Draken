#pragma once

class Item;

class Player
{
	public:
		Player();
		~Player();

	private:
		char name[15];
		int level;
		int hitpoints;
		int experience;
		int attack;
		int deffence;
		Item* inventory[];
};

