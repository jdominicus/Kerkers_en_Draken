#include "RandomNumberGenerator.h"
#include "Application.h"

#include "StringClass.h"
#include "UserInterface.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <iostream>

int main()
{
	{
		Application application;
		application.start();
	}

	_CrtDumpMemoryLeaks();
}
