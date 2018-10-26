#pragma once

class Item;
class Room;
class Layer;
class Dungeon;
class StringClass;
class RandomNumberGenerator;

class Player
{
	public:
		Player(const char* name, int level, int hitpoints, int experience, int attack, int defence, Dungeon& dungeon);
		~Player();

	private:
		int level;
		int hitpoints;
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

		void addExperience(int experience);
		void changeStats(int hitpoints, int attack, int defence);

		void displayStats();
		void displayInventory();
		void displayCurrentRoom();
		void displayCurrentLayer();
};

