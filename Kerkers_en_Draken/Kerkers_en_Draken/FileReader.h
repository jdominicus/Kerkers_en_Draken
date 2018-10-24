#pragma once
class FileReader
{
public:
	FileReader();
	~FileReader();
	void openFile();
	char* readLine();
};

