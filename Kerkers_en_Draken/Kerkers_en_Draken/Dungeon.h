#pragma once

class Layer;
class Room;
class Player;

class Dungeon
{
	public:
		Dungeon(int width, int height, int depth);
		~Dungeon();

	private:
		int width;
		int height;
		int depth;

		Layer** layers;
		Room* startRoom;
		Room* endRoom;

	public:
		Layer* getLayer(int index);
		Room* getStartRoom();
		Room* getEndRoom();
		void print();
};

