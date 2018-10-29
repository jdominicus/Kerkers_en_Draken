#include "FileHandler.h"

FileHandler::FileHandler()
{
}

FileHandler::~FileHandler()
{
}

void FileHandler::openMonsterFile()
{
	file.exceptions(std::ifstream::badbit); // No need to check failbit
	try 
	{
		file.open("monsters.txt");
	}
	catch (const std::ifstream::failure& e) 
	{
		std::cout << "Exception opening/reading file";
	}
}

void FileHandler::openHeroFile()
{
	file.exceptions(std::ifstream::badbit); // No need to check failbit
	try 
	{
		file.open("hero.txt");
	}
	catch (const std::ifstream::failure& e) 
	{
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
				ch = file.get();
				i++;
			}
			info[i] = ch;
			return info;
		}
		ch = file.get();
	}

	return info;
}

void FileHandler::writeInfo(char c)
{
	if (file.is_open())
	{
		file.put(c);
	}
}