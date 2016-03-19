#include "Controller.h"
#include "VirtualMaze.h"
#include "Logger.h"

using namespace std;

namespace Micromouse
{

	Controller::Controller()
	{
		VirtualMaze maze = VirtualMaze(31, 31);
		maze.generateRandomMaze();
		logC( DEBUG1 ) << maze; //log to console only
	}






	Controller::~Controller()
	{
	}


}
