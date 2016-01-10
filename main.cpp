#include "Application.h"

#include <iostream>

int main()
{
	try
	{
		Application game;
		game.Run();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}