#pragma once

#include <exception>

class MyException : public std::exception
{
	public:
		MyException();
		~MyException();
		virtual const char* what() const throw();
};

