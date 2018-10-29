#include "MyException.h"

MyException::MyException()
{
}

MyException::~MyException()
{
}

const char* MyException::what() const throw()
{
	return "Failed to allocate more memory!";
}

