#pragma once

class StringClass;

class Item
{
	public:
		Item();
		Item(const char* name);
		~Item();
		Item(const Item& other);
		Item(Item&& other);
		Item& operator=(Item& other);
		Item& operator=(Item&& other);

	private:
		StringClass* name;
};

