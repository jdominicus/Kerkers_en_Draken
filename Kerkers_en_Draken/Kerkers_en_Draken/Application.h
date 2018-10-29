#pragma once

#include "UserInterface.h"

class Dungeon;
class Player;
class StringClass;

class Application : public UserInterface
{
	public:
		Application();
		~Application();

	private:
		Dungeon* dungeon;
		Player* player;
		int gameState;
		bool running;

	public:
		void start();

	private:
		void createNewDungeon();
		void createNewPlayer();
		void createCustomPlayer();

		void displayOptions() const;
		int handleUserInput() const;
		void handleOptions(int option);
};
