#pragma once

class Room;
class Dungeon;

class Layer
{
	public:
		Layer(int width, int height, int minLevelMonsters, int maxLevelMonsters, Dungeon& dungeon);
		~Layer();
	
	private:
		const int width;
		const int height;
		const int minLevelMonsters;
		const int maxLevelMonsters;

		Room** rooms;
		Room* startRoom;
		Room* endRoom;
		Dungeon* const dungeon;

	public:
		int getMinLevelMonsters() const;
		int getMaxLevelMonsters() const;
		Room* getStartRoom() const;
		void setStartRoom(int index);
		Room* getEndRoom() const;
		void setEndRoom(int index);
		Room* getRooms(int index) const;
		void print() const;
};

