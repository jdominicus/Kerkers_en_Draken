#pragma once

#include "UserInterface.h"

class Item;
class Room;
class Layer;
class Dungeon;
class StringClass;
class RandomNumberGenerator;

class Player : public UserInterface
{
	public:
		Player(const char* name, Dungeon& dungeon);
		Player(const char* name, int level, int experience, int hitpoints, int maxHitpoints, int attack, int defence, Dungeon& dungeon);
		~Player();

	private:
		int level;
		int hitpoints;
		int maxHitpoints;
		int experience;
		int attack;
		int defence;

		StringClass* name;
		Room* currentRoom;
		Layer* currentLayer;
		Dungeon* dungeon;
		Item* inventory[5];

	public:
		Layer* getLayer();
		void pickUpItem();
		void useItem(int index);
		void move(int direction);
		void rest();
		void fight();
		void run();

		void addExperience(int experience);
		void changeStats(int hitpoints, int attack, int defence);

		void displayStats();
		void displayInventory();
		void displayCurrentRoom();
		void displayCurrentLayer();
};

