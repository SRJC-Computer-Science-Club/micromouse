#include <iostream>
#include "Controller.h"
#include "CompactMaze.h"

using namespace std;

namespace Micromouse
{

	Controller::Controller()
	{
		CompactMaze maze = CompactMaze(31, 31);
		maze.setExplored(true, 14, 14);
		maze.setExplored(true, 14, 16);
		maze.setExplored(true, 16, 14);
		maze.setExplored(true, 16, 16);
		maze.setOpen(true, 14, 14);
		maze.setOpen(true, 14, 16);
		maze.setOpen(true, 16, 14);
		maze.setOpen(true, 16, 16);

		maze.setExplored(true, 14, 15);
		maze.setExplored(true, 15, 14);
		maze.setExplored(true, 16, 15);
		maze.setExplored(true, 15, 16);
		maze.setOpen(true, 14, 15);
		maze.setOpen(true, 15, 14);
		maze.setOpen(true, 16, 15);
		maze.setOpen(true, 15, 16);

		maze.generateRandomMap();
		cout << maze;
		system("pause");
	}






	Controller::~Controller()
	{
	}


}