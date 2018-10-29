#pragma once
#include <iostream>
#include <fstream>
#include "StringClass.h"

#define lineLength 100

class FileHandler
{
public:
	FileHandler();
	~FileHandler();
	void openMonsterFile();
	void openHeroFile();
	void closeFile();
	char* readInfo();
	void writeInfo(char c);

private:
	std::fstream file;
	char info[lineLength];
};

