#include "Controller.h"
#include "VirtualMaze.h"
#include "Logger.h"
#include "MouseBot.h"

using namespace std;

namespace Micromouse
{

	Controller::Controller()
	{
		//VirtualMaze maze = VirtualMaze(31, 31);
		//maze.generateRandomMaze();

		MouseBot mouse = MouseBot(PositionVector(0,0));
		mouse.mapMaze();

		//logC( DEBUG1 ) << maze; //log to console only
	}






	Controller::~Controller()
	{
	}


}
