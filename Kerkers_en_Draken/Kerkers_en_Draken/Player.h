#pragma once

#include "UserInterface.h"

#define INV_SPACE 5

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
		Item* inventory[INV_SPACE];
		Room* currentRoom;
		Layer* currentLayer;
		Dungeon* const dungeon;

	public:
		Room* getCurrentRoom() const;
		Layer* getLayer() const;
		void pickUpItem();
		void useItem();
		void rest();
		void fight();
		void run();

		void addExperience(int experience);
		void changeStats(int hitpoints, int attack, int defence);
		int getHealth() const;

		void displayStats() const;
		void displayInventory() const;
		void displayCurrentLayer() const;

		int getAttributes(int index) const;
		StringClass* getName() const;
		//Item* getInventory(int index) const;
};

