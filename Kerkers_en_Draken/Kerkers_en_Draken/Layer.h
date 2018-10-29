#pragma once
#include "Dungeon.h"

class Room;
class Dungeon;

class Layer
{
	public:
		Layer(int width, int height, Dungeon& dungeon, int layerLevel);
		~Layer();
	
	private:
		const int width;
		const int height;
		const int layerLevel;

		Room** rooms;
		Room* startRoom;
		Room* endRoom;
		Dungeon* const dungeon;

	public:
		int getLayerLevel() const;
		Room* getStartRoom() const;
		void setStartRoom(int index);
		Room* getEndRoom() const;
		void setEndRoom(int index);
		Room* getRooms(int index) const;
		void print() const;
		Room* getDungeonEndRoom() const;
};

