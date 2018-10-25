#pragma once

class Room;
class Dungeon;
class RandomNumberGenerator;

class Layer
{
	public:
		Layer(int width, int height, int minLevelMonsters, int maxLevelMonsters, Dungeon* , RandomNumberGenerator* random);
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
		RandomNumberGenerator* random;

	public:
		int getMinLevelMonsters();
		int getMaxLevelMonsters();
		Room* getStartRoom();
		Room* getEndRoom();

		void print();
};

