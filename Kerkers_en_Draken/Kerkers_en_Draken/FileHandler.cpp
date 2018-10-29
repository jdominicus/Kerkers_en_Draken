#include "FileHandler.h"

FileHandler::FileHandler()
{
	//mf = new MonsterFactory();
}

FileHandler::~FileHandler()
{
}

void FileHandler::openMonsterFile()
{
	file.exceptions(std::ifstream::badbit); // No need to check failbit
	try {
		file.open("monsters.txt");
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception opening/reading file";
	}
}

void FileHandler::closeFile()
{
	file.close();
}

char* FileHandler::readInfo()
{
	char ch = file.get();
	while (!file.eof())
	{
		if (ch == '[')
		{
			ch = file.get();
			int i = 0;
			while (ch != ']')
			{
				info[i] = ch;
				std::cout << ch;
				ch = file.get();
				i++;
			}
			info[i] = ch;
			std::cout << std::endl;
			return info;
		}
		ch = file.get();
	}

	return info;
}
