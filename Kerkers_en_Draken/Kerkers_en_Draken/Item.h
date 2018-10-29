#pragma once

class Player;
class StringClass;

class Item
{
	public:
		Item(int id, const char* name);
		~Item();

	private:
		const int id;
		const StringClass* const name;

	public:
		void use(Player& player);
		const char* getName() const;
};

