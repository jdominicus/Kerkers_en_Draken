#pragma once
class Monster
{
	public:
		Monster();
		~Monster();

	private:
		const char name[30];		//naam max 30 karakters
		const int level;			//1-10 gevaarlijkheid / BAAS voor eindbaas
		int attack;					//percentage voor hitrate
		const int strengthMin;		//minimum schadepunten
		int strengthMax;			//maximum schadepunten
		int defence;				//percentage voor ontwijken
		int hp;						//levenspunten
};

/*
	naam: 		naam van het monster
	level: 		1 is het minst gevaarlijk 10 het meest. Staat hier "BAAS" dan gaat het om een eindmonster
	aanval: 	voor de x => het percentage kans dat de aanval raakt. na de x => hoe vaak dit monster per keer aanvalt
	schade: 	respectievelijk het minimum aantal schadepunten dat een geslaagde aanval toebrengt en het maximum aantal schadepunten, gescheiden door een min teken
	verdediging: 	het percentage kans dat een geslaagde aanval van de held toch afgeweerd of ontweken wordt door het monster
	levenspunten: 	hoe veel schadepunten een monster kan incasseren voordat deze verslagen is
*/
