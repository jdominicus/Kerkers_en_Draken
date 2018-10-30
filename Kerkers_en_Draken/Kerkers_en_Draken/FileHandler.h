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
	void openHeroFile(int readWrite);
	void closeFile();
	char* readInfo();
	void writeInfo(StringClass str);

private:
	std::ifstream file;
	std::ofstream write;
	char info[lineLength];
};

