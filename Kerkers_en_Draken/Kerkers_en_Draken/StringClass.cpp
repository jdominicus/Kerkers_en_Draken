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

StringClass::StringClass(const StringClass& other)
{	
	char* newString = new char[strlen(other.charArray) + 1];
	strcpy_s(newString, strlen(other.charArray) + 1, other.charArray);
	this->charArray = newString;
}

const char* StringClass::getCharArray() const
{
	return this->charArray;
}

int StringClass::getLength() const
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

void StringClass::empty()
{
	delete[] charArray;
	char* newString = new char[1];
	newString[0] = '\0';
	charArray = newString;
}
