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
		Item* item;
		Monster* monster;
		StringClass* description;
		Layer* const layer;

	public:
		void setStartRoom();
		void setEndRoom();
		void setVisited();
		bool isVisited();
		char getRoomType() const;
		StringClass* getDescription() const;
		Room* getRoom(int index) const;
		void setRoom(int index, Room* room);
		Item* getItem() const;
		void removeItem();
		void setMonster();
		Monster* getMonster() const;
		void destroyMonster();
		Layer* getLayer() const;
		void print() const;

	private:
		void createDescription();
		void createItem();
};

