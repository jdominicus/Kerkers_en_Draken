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
		const int width;
		const int height;
		const int depth;

		Layer** layers;
		Room* startRoom;
		Room* endRoom;

	public:
		Layer* getLayer(int index) const;
		Room* getStartRoom() const;
		Room* getEndRoom() const;
		void print() const;
};

