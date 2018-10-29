#pragma once
#include <iostream>
#include <fstream>
#include "MonsterFactory.h"

class FileReader
{
public:
	FileReader();
	~FileReader();
	void openFile();
	void readLine();

private:
	std::ifstream file;
	MonsterFactory* mf;
};

