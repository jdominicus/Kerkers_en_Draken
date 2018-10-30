#pragma once

class StringClass;

class Monster
{
	public:
		Monster(StringClass* name, int level, int attack, int nrOfAttacks, int strengthMin, int strengthMax, int defence, int hp);
		~Monster();
		Monster(const Monster& other);

	private:
		StringClass* name;			//naam max 30 karakters
		const int level;			//1-10 gevaarlijkheid / 25 voor eindbaas
		int attack;					//0-100 percentage voor hitrate
		const int nrOfAttacks;		//1-9 aantal keren dat het monster aanvalt
		const int strengthMin;		//0-9 minimum schadepunten
		int strengthMax;			//1-99 maximum schadepunten
		int defence;				//10-99 percentage voor ontwijken
		int hp;						//1-999 levenspunten

	public:
		const char* getName() const;
		int getLevel() const;
		void reduceHealth(int health);
		int getHealth() const;
		int getAttack();
		int getNrOfAttacks();
		int getStrenghtMin();
		int getStrenghtMax();
		int getDefence();
};
