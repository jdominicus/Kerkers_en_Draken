#include "RandomNumberGenerator.h"
#include "Application.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <iostream>

int main()
{
	{
		try
		{
			Application application;
			application.start();
		}
		catch (int error)
		{
			switch (error)
			{
				case 0: std::cout << "Bad allocation error!" << std::endl;
			}
		}
	}

	_CrtDumpMemoryLeaks();
}
