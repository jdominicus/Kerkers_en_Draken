#pragma once

class Layer;
class Room;
class Player;
class RandomNumberGenerator;

class Dungeon
{
	public:
		Dungeon(int width, int height, int depth, RandomNumberGenerator* random);
		~Dungeon();

	private:
		int width;
		int height;
		int depth;

		Layer** layers;
		Player* player;
		RandomNumberGenerator* random;

	public:
		Layer* getLayer(int index);
		void print();
};

