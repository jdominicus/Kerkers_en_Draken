#pragma once
class Player
{
	public:
		Player();
		~Player();

	private:
		char name[15];
		unsigned int level;
		unsigned int hitpoints;
		unsigned int experience;
		unsigned int attack;
		unsigned int deffence;
		char* inventory;
};

