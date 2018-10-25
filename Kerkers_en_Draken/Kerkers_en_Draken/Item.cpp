#include "Item.h"
#include "StringClass.h"

Item::Item() : Item("Error")
{
}

Item::Item(const char* name) : name{ new StringClass(name) }
{
}

Item::~Item()
{
}

Item::Item(const Item& other)
{
	this->name = new StringClass(other.name->getCharArray());
}

Item::Item(Item&& other)
{
	this->name = other.name;
	other.name = nullptr;
}

Item& Item::operator=(Item& other)
{
	if (name != nullptr)
		delete name;

	this->name = new StringClass(other.name->getCharArray());

	return *this;
}

Item& Item::operator=(Item&& other)
{
	if (name != nullptr)
		delete name;

	this->name = other.name;
	other.name = nullptr;

	return *this;
}
