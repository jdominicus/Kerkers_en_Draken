#pragma once
#include <iostream>
#include <fstream>

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

private:
	std::ifstream file;
	char info[lineLength];
	//MonsterFactory* mf;
};

