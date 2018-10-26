#pragma once

#include <Random>
#include <ctime>

class Item;
class Monster;
class Layer;
class StringClass;

class Room
{
	public:
		Room(Layer& layer);
		~Room();

	private:
		bool clean;
		int size;
		int layout;
		bool startRoom;
		bool endRoom;
		bool visited;
		char roomType;

		Room* rooms[6]; // North - East - South - West - Up - Down
		Layer* layer;
		Item* item;
		Monster* monster;
		StringClass* description;

	public:
		void setStartRoom();
		void setEndRoom();
		void setVisited();
		bool isVisited();
		char getRoomType();
		StringClass* getDescription();
		Room* getRoom(int index);
		void setRoom(int index, Room* room);
		Item* getItem();
		void removeItem();
		Layer* getLayer();
		void destroyMonster();

	private:
		void createDescription();
		void createItem();
		void createMonster();
};

