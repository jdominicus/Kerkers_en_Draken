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
		Player(const char* name, int level, int hitpoints, int experience, int attack, int deffence, Dungeon* dungeon);
		~Player();

	private:
		int level;
		int hitpoints;
		int experience;
		int attack;
		int deffence;

		StringClass* name;
		Room* currentRoom;
		Layer* currentLayer;
		Dungeon* dungeon;
		Item* inventory[5];

	public:
		Layer* getLayer();
		void pickUpItem();
		void move(int direction);
		void displayCurrentRoom();
		void displayCurrentLayer();
};

