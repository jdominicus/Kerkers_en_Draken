#pragma once
class Monster
{
	public:
		Monster(char name[], int level, int attack, int nrOfAttacks,
					int strengthMin, int strengthMax, int defence, int hp);
		~Monster();

	private:
		char name[30];				//naam max 30 karakters
		const int level;			//1-10 gevaarlijkheid / 25 voor eindbaas
		int attack;					//0-100 percentage voor hitrate
		const int nrOfAttacks;		//1-9 aantal keren dat het monster aanvalt
		const int strengthMin;		//0-9 minimum schadepunten
		int strengthMax;			//1-99 maximum schadepunten
		int defence;				//10-99 percentage voor ontwijken
		int hp;						//1-999 levenspunten
};

/*
	naam: 		naam van het monster
	level: 		1 is het minst gevaarlijk 10 het meest. Staat hier "BAAS" dan gaat het om een eindmonster
	aanval: 	voor de x => het percentage kans dat de aanval raakt. na de x => hoe vaak dit monster per keer aanvalt
	schade: 	respectievelijk het minimum aantal schadepunten dat een geslaagde aanval toebrengt en het maximum aantal schadepunten, gescheiden door een min teken
	verdediging: 	het percentage kans dat een geslaagde aanval van de held toch afgeweerd of ontweken wordt door het monster
	levenspunten: 	hoe veel schadepunten een monster kan incasseren voordat deze verslagen is
*/
