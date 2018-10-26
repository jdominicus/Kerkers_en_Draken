#pragma once

class Room;
class Dungeon;

class Layer
{
	public:
		Layer(int width, int height, int minLevelMonsters, int maxLevelMonsters, Dungeon& dungeon);
		~Layer();
	
	private:
		int width;
		int height;
		int minLevelMonsters;
		int maxLevelMonsters;

		Room** rooms;
		Room* startRoom;
		Room* endRoom;
		Dungeon* dungeon;

	public:
		int getMinLevelMonsters();
		int getMaxLevelMonsters();
		Room* getStartRoom();
		void setStartRoom(int index);
		Room* getEndRoom();
		void setEndRoom(int index);
		Room* getRooms(int index);

		void print();
};

