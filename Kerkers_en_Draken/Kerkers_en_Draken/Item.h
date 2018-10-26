#pragma once

class Player;
class StringClass;

class Item
{
	public:
		Item(int id, const char* name);
		~Item();

	private:
		int id;
		StringClass* name;

	public:
		void use(Player& player);
		const char* getName();
};

