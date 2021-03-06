#pragma once

class StringClass;

class UserInterface
{
	public:
		UserInterface();
		~UserInterface();
		
		int getInputInt(const char* message, int min, int max) const;
		StringClass getInputString(const char* message, int min, int max) const;
};

