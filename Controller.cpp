#include <iostream>
#include "Controller.h"
#include "CompactMaze.h"

using namespace std;

namespace Micromouse
{

	Controller::Controller()
	{
		CompactMaze maze = CompactMaze(31, 31);
		maze.generateRandomMap();
		cout << maze;
		system("pause");
	}






	Controller::~Controller()
	{
	}


}