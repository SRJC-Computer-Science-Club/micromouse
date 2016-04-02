#include "Controller.h"
#include "Logger.h"
#include "MouseBot.h"
#include <vector>



namespace Micromouse
{

	Controller::Controller()
	{
		log(INFO) << "Starting Program"; //log to console only

		MouseBot mouse(0,0);
		mouse.testMotors();
		//mouse.mapMaze();

		logC( DEBUG1 ) << "End Program"; //log to console only
	}






	Controller::~Controller()
	{
	}


}
