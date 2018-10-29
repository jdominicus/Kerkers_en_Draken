#include "FileReader.h"

#define lineLength 100

FileReader::FileReader()
{
	mf = new MonsterFactory();
}

FileReader::~FileReader()
{
}

void FileReader::openFile()
{
	file.exceptions(std::ifstream::badbit); // No need to check failbit
	try {
		//file.open("C:/Users/remco/Desktop/Remco/School/Minor/CPP1/Eindopdracht/monsters.txt");
		file.open("monsters.txt");
		while (!file.eof())
		{
			readLine();
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception opening/reading file";
	}

	file.close();
}

void FileReader::readLine()
{
	char info[lineLength];
	char ch = file.get();
	if (!file.eof())
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
			mf->addMonster(info);
		}
		ch = file.get();
	}
}
