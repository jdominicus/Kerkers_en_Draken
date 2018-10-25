#include "StringClass.h"

#include <iostream>

StringClass::StringClass(const char* string)
{
	char* newString = new char[strlen(string) + 1];
	strcpy_s(newString, strlen(string) + 1, string);
	charArray = newString;
}

StringClass::~StringClass()
{
	delete[] charArray;
}

const char* StringClass::getCharArray()
{
	return this->charArray;
}

int StringClass::getLength()
{
	return strlen(charArray);
}

void StringClass::append(const char* string)
{	
	char* newString = new char[strlen(charArray) + strlen(string) + 1];
	strcpy_s(newString, strlen(charArray) + strlen(string) + 1, charArray);
	strcat_s(newString, strlen(charArray) + strlen(string) + 1, string);

	delete[] charArray;
	charArray = newString;
}

void StringClass::print()
{
	std::cout << charArray;
}
