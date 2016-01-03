#include "Game.h"

#include <iostream>

int main()
{
	try
	{
		Game game;
		game.Run(60);
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}